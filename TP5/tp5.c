/*
 * TP 5 -- From a mesh to a sparse linear system.
 *
 * Compile:  gcc -Wall tp5.c -o tp5
 * Run:      ./tp5
 *
 * Part 0 is provided: it contains the structures of TP 2 (meshes) and TP 3 (edge table).
 * Parts 1 to 4 correspond to Exercises 1 to 4 of the sheet: complete the functions marked TODO.
 * Part 5 is provided: functions which print what you have built.
 * In main(), at the end of the file, add the lines given in each exercise of the sheet.
 */
#include <stdio.h>
#include <stdlib.h>

/* Absolute value and maximum of two doubles (so that no math library is needed). */
double absval(double a) { return a < 0 ? -a : a; }
double maxval(double a, double b) { return a > b ? a : b; }

/* ======================================================================================
 * Part 0 (provided). Meshes (TP 2) and edge table (TP 3)
 * ====================================================================================== */

struct Vertex
{
  double x;
  double y;
};

struct Triangle
{
  int v[3]; /* indices of the 3 vertices in the vertex array, counterclockwise */
};

struct Mesh2D
{
  int nv;               /* number of vertices  */
  struct Vertex *vert;  /* array of nv vertices */
  int nt;               /* number of triangles */
  struct Triangle *tri; /* array of nt triangles */
};

int initialize_mesh2D(struct Mesh2D *m, int nv, int nt)
{
  m->nv = nv;
  m->nt = nt;
  m->vert = malloc(nv * sizeof(struct Vertex));
  m->tri = malloc(nt * sizeof(struct Triangle));
  return (m->vert && m->tri) ? 0 : -1;
}

void dispose_mesh2D(struct Mesh2D *m)
{
  free(m->vert);
  free(m->tri);
}

/* Signed area of triangle t: positive if its vertices are counterclockwise. */
double triangle_area(const struct Mesh2D *m, int t)
{
  struct Vertex a = m->vert[m->tri[t].v[0]];
  struct Vertex b = m->vert[m->tri[t].v[1]];
  struct Vertex c = m->vert[m->tri[t].v[2]];
  return 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

/* Writes the mesh for gnuplot:  gnuplot -p -e "plot 'mesh.dat' with lines" */
int mesh2D_to_gnuplot(const struct Mesh2D *m, const char *filename)
{
  FILE *f = fopen(filename, "w");
  if (!f)
    return -1;
  for (int t = 0; t < m->nt; ++t)
  {
    for (int k = 0; k <= 3; ++k)
    {
      struct Vertex p = m->vert[m->tri[t].v[k % 3]];
      fprintf(f, "%g %g\n", p.x, p.y);
    }
    fprintf(f, "\n");
  }
  fclose(f);
  return 0;
}

/* Edge table of TP 3. Edge j (j = 0, 1, 2) of triangle i is the oriented edge
 * v[j] -> v[(j+1)%3]; its code is 3*i + j. All the edges starting at a vertex v are
 * obtained by following the chain
 *     e = head[v],  e = next[e],  e = next[e], ...   until e == -1.                     */
struct EdgeTable
{
  int *head; /* size nv   */
  int *next; /* size 3*nt */
};

struct EdgeTable build_edge_table(const struct Mesh2D *m)
{
  struct EdgeTable et;
  et.head = malloc(m->nv * sizeof(int));
  et.next = malloc(3 * m->nt * sizeof(int));
  for (int v = 0; v < m->nv; ++v)
    et.head[v] = -1;
  for (int i = 0; i < m->nt; ++i)
    for (int j = 0; j < 3; ++j)
    {
      int v1 = m->tri[i].v[j];
      int code = 3 * i + j;
      et.next[code] = et.head[v1]; /* push the edge on the chain of v1 */
      et.head[v1] = code;
    }
  return et;
}

void dispose_edge_table(struct EdgeTable *et)
{
  free(et->head);
  free(et->next);
}

/* Second vertex of the edge with the given code. */
int edge_end(const struct Mesh2D *m, int code)
{
  int i = code / 3, j = code % 3;
  return m->tri[i].v[(j + 1) % 3];
}

/* Returns the code of the oriented edge v1 -> v2, or -1 if there is no such edge. */
int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh2D *m)
{
  for (int e = et->head[v1]; e != -1; e = et->next[e])
    if (edge_end(m, e) == v2)
      return e;
  return -1;
}

/* Boundary temperature: 100 on the left edge, 0 on the right edge, linear in between. */
const double L = 2.0, H = 1.0; /* the plate is [0,L] x [0,H] */

double g(double x, double y)
{
  (void)y; /* g does not depend on y */
  return 100.0 * (1.0 - x / L);
}

/* ======================================================================================
 * Part 1 (Exercise 1). The mesh of the plate.
 * ====================================================================================== */

/* Mesh of [0,L] x [0,H] with nx x ny cells. Vertex (i,j) has index j*(nx+1) + i and
 * coordinates (i*L/nx, j*H/ny). Let v00, v10, v01, v11 be the lower left, lower right,
 * upper left, upper right vertices of cell (i,j). The cell is cut along a diagonal:
 *   if i+j is even:  triangles (v00, v10, v11) and (v00, v11, v01),
 *   if i+j is odd:   triangles (v00, v10, v01) and (v10, v11, v01).
 * Returns 0 on success, -1 otherwise. */
int plate_mesh2D(struct Mesh2D *m, int nx, int ny)
{
  int nv = (nx + 1) * (ny + 1);
  int nt = 2 * nx * ny;
  if (initialize_mesh2D(m, nv, nt) == -1)
  {
    dispose_mesh2D(m);
    return -1;
  }
  // we must now fill the mesh correctly
  // we populate the vertices
  double dx = L / nx;
  double dy = H / ny;

  int k = 0;
  for (int j = 0; j <= ny; j++)
  {
    double y = j * dy;
    for (int i = 0; i <= nx; i++)
    {
      m->vert[k].x = i * dx;
      m->vert[k].y = y;
      k++;
    }
  }
  int t = 0;

  for (int j = 0; j < ny; j++)
  {
    for (int i = 0; i < nx; i++)
    {
      int v00 = j * (nx + 1) + i;
      int v10 = v00 + 1;
      int v01 = v00 + (nx + 1);
      int v11 = v01 + 1;

      if ((i + j) % 2 == 0)
      {
        m->tri[t].v[0] = v00;
        m->tri[t].v[1] = v10;
        m->tri[t].v[2] = v11;
        t++;

        m->tri[t].v[0] = v00;
        m->tri[t].v[1] = v11;
        m->tri[t].v[2] = v01;
        t++;
      }
      else
      {
        m->tri[t].v[0] = v00;
        m->tri[t].v[1] = v10;
        m->tri[t].v[2] = v01;
        t++;

        m->tri[t].v[0] = v10;
        m->tri[t].v[1] = v11;
        m->tri[t].v[2] = v01;
        t++;
      }
    }
  }

  return 0;
}

/* ======================================================================================
 * Part 2 (Exercise 2). Boundary vertices and neighbours.
 * ====================================================================================== */

/* Returns an array of m->nv integers (allocated here): 1 for a boundary vertex, 0 otherwise.
 * An edge a -> b lies on the boundary if the opposite edge b -> a does not exist. */
int *boundary_vertices(const struct Mesh2D *m, const struct EdgeTable *et)
{
  int *on_bdry = calloc(m->nv, sizeof(int));
  if (!on_bdry)
    return NULL;

  for (int v = 0; v < m->nv; v++)
  {
    for (int e = et->head[v]; e != -1; e = et->next[e])
    {
      int w = edge_end(m, e);
      if (edge_table_find(w, v, et, m) == -1) /*the inverted edge is w->v */
      {
        on_bdry[v] = 1;
        on_bdry[w] = 1;
      }
    }
  }
  return on_bdry;
}

/* Writes the neighbours of v into nbrs, each one once, and returns their number (the degree
 * of v). The neighbours of v are the other vertices of the triangles containing v.
 * The chain of v in the edge table contains one edge per triangle containing v: the edge
 * with code e belongs to triangle i = e / 3, where v is the vertex number j = e % 3.
 * The array nbrs must be large enough. */
int vertex_neighbours(int v, const struct EdgeTable *et, const struct Mesh2D *m, int *nbrs)
{
  int count = 0;

  for (int e = et->head[v]; e != -1; e = et->next[e])
  {
    int i = e / 3; /* triangle index */
    int j = e % 3; /* local vertex index */

    int w1 = m->tri[i].v[(j + 1) % 3];
    int flag = 0;
    for (int k = 0; k < count; k++)
    {
      if (nbrs[k] == w1)
      {
        flag = 1;
        break;
      }
    }
    if (flag != 1)
    {
      nbrs[count++] = w1;
    }

    int w2 = m->tri[i].v[(j + 2) % 3];
    flag = 0;
    for (int k = 0; k < count; k++)
    {
      if (nbrs[k] == w2)
      {
        flag = 1;
        break;
      }
    }
    if (flag != 1)
    {
      nbrs[count++] = w2;
    }
  }

  return count;
}

/* ======================================================================================
 * Part 3 (Exercise 3). The linear system in CRS format.
 * ====================================================================================== */

#define MAX_NBRS 16 /* maximal number of neighbours of a vertex (8 on our meshes) */

/* Compressed Row Storage (CRS), also called CSR. */
struct CSRMatrix
{
  int n;        /* the matrix is n x n */
  int nnz;      /* number of stored entries */
  double *val;  /* size nnz: the values, row after row */
  int *col_ind; /* size nnz: the column of each value */
  int *row_ptr; /* size n+1: row i is stored at positions row_ptr[i], ..., row_ptr[i+1]-1 */
};

/* Provided. */
int csr_initialize(struct CSRMatrix *A, int n, int nnz)
{
  A->n = n;
  A->nnz = nnz;
  A->val = malloc(nnz * sizeof(double));
  A->col_ind = malloc(nnz * sizeof(int));
  A->row_ptr = malloc((n + 1) * sizeof(int));
  return (A->val && A->col_ind && A->row_ptr) ? 0 : -1;
}

/* Provided. */
void csr_dispose(struct CSRMatrix *A)
{
  free(A->val);
  free(A->col_ind);
  free(A->row_ptr);
}

/* Provided. */
void csr_print(const struct CSRMatrix *A)
{
  printf("  n = %d, nnz = %d\n  val     =", A->n, A->nnz);
  for (int k = 0; k < A->nnz; ++k)
    printf(" %g", A->val[k]);
  printf("\n  col_ind =");
  for (int k = 0; k < A->nnz; ++k)
    printf(" %d", A->col_ind[k]);
  printf("\n  row_ptr =");
  for (int i = 0; i <= A->n; ++i)
    printf(" %d", A->row_ptr[i]);
  printf("\n");
}

/*The functions csr_initialize, csr_dispose and csr_print are provided. In the functions
below, to get the neighbours of a vertex v, declare an array int nbrs[MAX_NBRS]; and call int
d = vertex_neighbours(v, et, m, nbrs);: then d is the degree of v, and its neighbours are
nbrs[0], . . . , nbrs[d-1].
1) Complete number_unknowns, which sets num[v] to −1 for a boundary vertex, numbers the
interior vertices 0, 1, . . . , N − 1 in increasing order, and returns N .


/* num[v] = -1 if v is a boundary vertex; otherwise num[v] is the number of the unknown at v:
 * the interior vertices are numbered 0, 1, ..., N-1 in increasing order. Returns N. */
int number_unknowns(const int *on_bdry, int nv, int *num)
{
  int count = 0;
  for (int i = 0; i < nv; i++)
  {
    if (on_bdry[i] == 1)
      num[i] = -1;
    if (on_bdry[i] == 0)
    {
      num[i] = count;
      count++;
    }
  }
  return count;
}

/*2) Complete count_nonzeros, which returns the number of nonzero entries of A: for each
interior vertex, 1 (the diagonal entry) plus the number of its interior neighbours.


/* Number of nonzero entries of A: for each interior vertex, 1 (diagonal) plus the number
 * of its interior neighbours. */
int count_nonzeros(const struct Mesh2D *m, const struct EdgeTable *et, const int *num)
{
  int count = 0;
  int nbrs[MAX_NBRS];
  for (int i = 0; i < m->nv; i++)
  {
    if (num[i] != -1)
    {
      count++;
      int d = vertex_neighbours(i, et, m, nbrs);
      for (int j = 0; j < d; j++)
      {
        if (num[nbrs[j]] != -1)
        {
          count++;
        }
      }
    }
  }

  return count;
}
/*3) Complete assemble_plate. The array b is allocated by the caller, with N entries. The
function proceeds as follows.
• Allocate A with csr_initialize(A, N, count_nonzeros(m, et, num)).
• Set A->row_ptr[0] = 0, and use a variable pos, initialised to 0, for the next free posi-
tion in val and col_ind.
• Loop over the vertices. For an interior vertex v, with i = num[v], write row i: first the
diagonal entry deg(v), in column i; then −1 in column num[w] for each interior neighbour
w. Set b[i] = 0, then add the temperature g(m->vert[w].x, m->vert[w].y) of each
boundary neighbour w. At the end of the row, set A->row_ptr[i+1] = pos.
4
Since num increases with v, the rows are written in the order 0, 1, . . . , N − 1, so that row_ptr
is filled from left to right*/

/* Builds A (with csr_initialize) and fills b (allocated by the caller, size N).
 * For each interior vertex v, with i = num[v], row i contains:
 *   - first, the diagonal entry deg(v) in column i,
 *   - then, the entry -1 in column num[w] for each interior neighbour w,
 * and b[i] is the sum of g(w) over the boundary neighbours w.
 * Returns 0 on success, -1 otherwise. */
int assemble_plate(const struct Mesh2D *m, const struct EdgeTable *et, const int *num, int N,
                   struct CSRMatrix *A, double *b)
{
  /* TODO: 1) call csr_initialize with n = N and nnz = count_nonzeros(m, et, num),
   *       2) set A->row_ptr[0] = 0 and int pos = 0 (next free position in val, col_ind),
   *       3) loop over the vertices; for each interior vertex v, with i = num[v]:
   *          write the diagonal entry, then the entries of the interior neighbours,
   *          set b[i] = 0 and add g(w) for each boundary neighbour w,
   *          and set A->row_ptr[i+1] = pos at the end of the row.                       */

  if (csr_initialize(A, N, count_nonzeros(m, et, num)) != 0)
    return -1;
  A->row_ptr[0] = 0;
  int nbrs[MAX_NBRS];
  int pos = 0;
  for (int i = 0; i < m->nv; i++)
  {
    if (num[i] != -1)
    {
      int deg = vertex_neighbours(i, et, m, nbrs);
      int row_index = num[i];
      A->val[pos] = deg;
      A->col_ind[pos] = row_index;
      pos++;
      b[row_index] = 0;
      for (int j = 0; j < deg; j++)
      {
        if (num[nbrs[j]] != -1)
        {
          A->val[pos] = -1;
          A->col_ind[pos] = num[nbrs[j]];
          pos++;
        }
        else
        {
          b[row_index] += g(m->vert[nbrs[j]].x, m->vert[nbrs[j]].y);
        }
      }
      A->row_ptr[row_index + 1] = pos;
    }
  }

  return 0;
}

/* ======================================================================================
 * Part 4 (Exercise 4). Matrix-vector product y = A x.
 * ====================================================================================== */

/* y must have room for A->n values. */
/*Exercise 4. Matrix–vector product.
1) Complete csr_matvec, which computes y = Ax, i.e. yi = ∑
j aij xj , using only the stored
entries: for each row i, sum val[k] * x[col_ind[k]] over the positions k of row i. How
many multiplications does it perform? How many would a product with the full N × N
matrix need?
2) Add to main:
double ones[3] = {1, 1, 1}, y[3];
csr_matvec(&A, ones, y);
print_vector("A * (1, 1, 1)", y, 3);
You should get (7, 2, 7). Explain why (Ax)i, for x = (1, . . . , 1), is the number of boundary
neighbours of interior vertex i.
At the end of main, release the memory:
free(on_bdry); csr_dispose(&A); dispose_edge_table(&et); dispose_mesh2D(&m);*/

void csr_matvec(const struct CSRMatrix *A, const double *x, double *y)
{
  for (int i = 0; i<A->n; i++)
  {
    y[i] = 0;
    for (int j = A->row_ptr[i]; j<A->row_ptr[i+1]; j++)
    {
      y[i] = y[i] + A->val[j] * x[A->col_ind[j]];
    }
  }
}

/* ======================================================================================
 * Part 5 (provided). Printing what you have built, to compare it with the sheet.
 * ====================================================================================== */

void print_mesh(const struct Mesh2D *m)
{
  printf("%d vertices:\n", m->nv);
  for (int v = 0; v < m->nv; ++v)
    printf("  vertex %2d = (%g, %g)\n", v, m->vert[v].x, m->vert[v].y);
  printf("%d triangles:\n", m->nt);
  for (int t = 0; t < m->nt; ++t)
    printf("  triangle %2d = (%d, %d, %d)\n", t, m->tri[t].v[0], m->tri[t].v[1], m->tri[t].v[2]);
}

void print_neighbours(const struct Mesh2D *m, const struct EdgeTable *et, const int *on_bdry)
{
  int nbrs[MAX_NBRS];
  for (int v = 0; v < m->nv; ++v)
  {
    int d = vertex_neighbours(v, et, m, nbrs);
    const char *kind = (on_bdry == NULL) ? "?" : (on_bdry[v] ? "boundary" : "interior");
    printf("  vertex %2d (%s): %d neighbours:", v, kind, d);
    for (int k = 0; k < d; ++k)
      printf(" %d", nbrs[k]);
    printf("\n");
  }
}

void print_numbering(const int *num, int nv)
{
  printf("  num =");
  for (int v = 0; v < nv; ++v)
    printf(" %d", num[v]);
  printf("\n");
}

/* Prints the CRS arrays, and the full matrix if it is small. */
void print_system(const struct CSRMatrix *A, const double *b)
{
  csr_print(A);
  if (A->n <= 10)
  {
    printf("  as a full matrix, with b on the right:\n");
    for (int i = 0; i < A->n; ++i)
    {
      double row[10] = {0};
      for (int k = A->row_ptr[i]; k < A->row_ptr[i + 1]; ++k)
        row[A->col_ind[k]] += A->val[k];
      printf("   ");
      for (int j = 0; j < A->n; ++j)
        printf(" %4g", row[j]);
      printf("   | %g\n", b[i]);
    }
  }
}

void print_vector(const char *name, const double *x, int n)
{
  printf("  %s =", name);
  for (int i = 0; i < n; ++i)
    printf(" %g", x[i]);
  printf("\n");
}

/* ======================================================================================
 * main: add the lines given in each exercise of the sheet.
 * ====================================================================================== */

int main(void)
{
  struct Mesh2D m;
  plate_mesh2D(&m, 4, 2);
  print_mesh(&m);
  mesh2D_to_gnuplot(&m, "mesh.dat");

  struct EdgeTable et = build_edge_table(&m);
  int *on_bdry = boundary_vertices(&m, &et);
  print_neighbours(&m, &et, on_bdry);

  int num[15];
  int N = number_unknowns(on_bdry, m.nv, num);
  print_numbering(num, m.nv);
  printf("  N = %d, nnz = %d\n", N, count_nonzeros(&m, &et, num));
  struct CSRMatrix A;
  double b[3];
  assemble_plate(&m, &et, num, N, &A, b);
  print_system(&A, b);

  /* 5) For nx = 2000, ny = 1000:
 *    - Interior vertices: N = (nx - 1) * (ny - 1) = 1999 * 999 = 1,997,001 (~2.00e6).
 *    - Full dense matrix: 8 * N^2 = 8 * (1,997,001)^2 ≈ 3.19e13 bytes (~31.9 TB / 29.0 TiB).
 *    - CSR format (nnz <= 9N): 8 * nnz + 4 * nnz + 4 * (N + 1) <= 112N + 4 bytes
 *      ≈ 2.24e8 bytes (~223.7 MB / 213.3 MiB). */

  double ones[3] = {1, 1, 1}, y[3];
  csr_matvec(&A, ones, y);
  print_vector("A * (1, 1, 1)", y, 3);

/* 1) Multiplications:
 *    - CSR matvec performs nnz multiplications (one per stored nonzero entry).
 *    - Full N x N dense matvec performs N^2 multiplications.
 *
 * 2) For x = (1, ..., 1), (Ax)_i is the sum of row i:
 *    - Diagonal entry is deg(v) (total neighbours), each interior neighbour contributes -1.
 *    - Thus (Ax)_i = deg(v) - (number of interior neighbours) = number of boundary neighbours. */

  free(on_bdry); csr_dispose(&A); dispose_edge_table(&et); dispose_mesh2D(&m);

  return 0;
}
