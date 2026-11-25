/*
 * TP 6 -- LU factorisation and pivoting.
 *
 * Compile:  gcc -Wall tp6.c -o tp6
 * Run:      ./tp6
 *
 * Part 0 is provided: dense matrices, printing, test matrices, timing.
 * Parts 1 to 3 correspond to the exercises of the sheet: complete the functions marked TODO.
 * In main(), at the end of the file, add the lines given in each exercise of the sheet.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <math.h>
#include <string.h>


/* ======================================================================================
 * Part 0 (provided). Dense matrices.
 * ====================================================================================== */

#define TOL 1e-12 /* in lu_pivot and count_nonzeros, |x| < TOL is considered to be zero */

/* An n x n matrix, stored row after row: entry (i,j) is a[i*n + j], for 0 <= i,j < n. */
struct DenseMatrix {
  int n;
  double *a;
};

double absval(double x) { return x < 0 ? -x : x; }

/* Allocates an n x n matrix filled with zeros. */
int dense_initialize(struct DenseMatrix *A, int n)
{
  A->n = n;
  A->a = calloc((size_t)n * n, sizeof(double));
  return A->a ? 0 : -1;
}

void dense_dispose(struct DenseMatrix *A) { free(A->a); }

/* Allocates B and copies A into it. */
int dense_copy(struct DenseMatrix *B, const struct DenseMatrix *A)
{
  if (dense_initialize(B, A->n)) return -1;
  for (int k = 0; k < A->n * A->n; ++k) B->a[k] = A->a[k];
  return 0;
}

/* Fills A (already allocated) with the n*n values of the array v, row after row. */
void dense_set(struct DenseMatrix *A, const double *v)
{
  for (int k = 0; k < A->n * A->n; ++k) A->a[k] = v[k];
}

void dense_print(const struct DenseMatrix *A)
{
  for (int i = 0; i < A->n; ++i) {
    printf("   ");
    for (int j = 0; j < A->n; ++j) printf(" %8.4g", A->a[i * A->n + j]);
    printf("\n");
  }
}

void print_vector(const char *name, const double *x, int n)
{
  printf("  %s =", name);
  for (int i = 0; i < n; ++i) printf(" %.6g", x[i]);
  printf("\n");
}

/* max_i |(Ax - b)_i| */
double residual(const struct DenseMatrix *A, const double *x, const double *b)
{
  int n = A->n;
  double r = 0.0;
  for (int i = 0; i < n; ++i) {
    double s = -b[i];
    for (int j = 0; j < n; ++j) s += A->a[i * n + j] * x[j];
    if (absval(s) > r) r = absval(s);
  }
  return r;
}

/* Random matrix with entries in [-1, 1]. */
void random_matrix(struct DenseMatrix *A)
{
  for (int k = 0; k < A->n * A->n; ++k) A->a[k] = 2.0 * rand() / RAND_MAX - 1.0;
}

/* Random matrix with entries in [-1, 1], plus n+1 on the diagonal: it is strictly diagonally
 * dominant, hence it admits an LU factorisation (Proposition 2.4). */
void random_dd_matrix(struct DenseMatrix *A)
{
  int n = A->n;
  random_matrix(A);
  for (int i = 0; i < n; ++i) A->a[i * n + i] += n + 1;
}

/* Elapsed processor time in seconds, to measure computing times:
 *   double t0 = seconds();  ... work ...;  double t = seconds() - t0;                    */
double seconds(void) { return (double)clock() / CLOCKS_PER_SEC; }

/* ======================================================================================
 * Part 1 (Exercises 1 and 2). LU factorisation without pivoting.
 * ====================================================================================== */

/* In-place LU factorisation, Algorithm 2.2 of the lecture notes. On output, T contains
 * L below the diagonal (the diagonal of L, made of ones, is not stored) and U on and above
 * the diagonal. Returns 0 on success, and -1 if a pivot T(p,p) = 0 is met. */
int lu_decompose(struct DenseMatrix *T)
{
  int n = T->n;
  double *m_T = T->a;
  /* TODO: translate Algorithm 2.2 into three nested loops (entry (i,j) is T->a[i*n + j]):
   *   for p = 0, ..., n-2:
   *     if T(p,p) == 0, return -1             (zero pivot: no LU without pivoting)
   *     for each row i > p:
   *       T(i,p) = T(i,p) / T(p,p)            (multiplier, stored in place of the zero)
   *       for each column j > p:
   *         T(i,j) = T(i,j) - T(i,p) * T(p,j)
   * Then check the last pivot T(n-1,n-1) in the same way, and return 0.                */

  for (int p = 0; p < n-1; p++){
    if(m_T[p * n + p] == 0) //pivot is 0
      return -1;
    double T_pp = m_T[p * n + p];
    for (int i = p + 1; i < n; i++){ // for each row i > p:
      m_T[i * n + p] = m_T[i * n + p] / T_pp;
      for (int j = p + 1; j < n; j++){ // for each column j > p:
        m_T[i * n + j] = m_T[i * n + j] - m_T[i * n + p] * m_T[p * n + j];
      }
    }
  }

  if(m_T[(n-1) * n + (n-1)] == 0){
    return -1;
  }
  return 0;
}

/* Solves A x = b, where T contains the LU factorisation of A (Algorithm 2.3).
 * On input, x contains b; on output, x contains the solution. */
void lu_solve(const struct DenseMatrix *T, double *x)
{
  /* TODO: 1) forward substitution with L (ones on the diagonal),
   *       2) backward substitution with U.                                              */

  int n = T->n;
  double *m_T = T->a;
  // L solve
  for (int j = 0; j < n; j++){
    for(int k = 0; k < j; k++){
      x[j] = x[j] - m_T[j * n + k] * x[k];
    }
  }
  // U solve
  for(int p = 0; p < n; p++){
    int j = (n - 1) - p;
    for(int k = j + 1; k < n ; k++){
      x[j] = x[j] - m_T[j * n + k] * x[k];
    }
    x[j] = x[j] / m_T[j * n + j];
  }
}

/* ======================================================================================
 * Part 2 (Exercise 5). LU factorisation with partial pivoting.
 * ====================================================================================== */

/* In-place PLU factorisation with partial pivoting, Algorithm 2.4 of the lecture notes.
 * perm (an array of n integers) describes P: on output, row i of PA is row perm[i] of A.
 * Returns 0 on success, and -1 if A is singular (all candidate pivots < TOL). */
int lu_pivot(struct DenseMatrix *T, int *perm)
{
  /* TODO: start with perm[i] = i. For each p: find the row q >= p with the largest
   * |T(q,p)|; if it is < TOL, return -1; swap rows p and q of T (all columns) and
   * perm[p], perm[q]; then eliminate below the pivot as in lu_decompose.               */
  
  int n = T->n;
  double *m_T = T->a;

  for (int i = 0; i < n; i++){
    perm[i] = i;
  }

  double *tmp_row = malloc(n * sizeof(double));
  //for each col p
  for (int p = 0; p < n; p++){
    //loop over col p to find the larges fabs(value)
    double max = 0;
    int q = p; //declared here to remember the line
    for (int i = p; i < n; i++){
      if(fabs(m_T[i * n + p]) > max){
        max = fabs(m_T[i * n + p]);
        q = i;
      }
    }
    if(max < TOL){
      free(tmp_row);
      return -1;
    }
    //swap row p and row q
    
    if(q != p){
      memcpy(tmp_row, &m_T[p*n],n*sizeof(double)); // store row p
      memcpy(&m_T[p*n], &m_T[q*n],n*sizeof(double)); // copy q to p
      memcpy(&m_T[q*n], tmp_row,n*sizeof(double)); //copy temp_p to q
      //swap perm[p] and perm[q]
      int tmp_perm = perm[p];
      perm[p] = perm[q];
      perm[q] = tmp_perm;
    }



    // gaussian elimination
    for(int i = p + 1; i < n; i++){
      m_T[i * n + p] =  m_T[i * n + p] / m_T[p * n + p];
      for(int j = p + 1; j < n; j++){
        m_T[i * n + j] = m_T[i * n + j] - m_T[i * n + p] * m_T[p * n + j];
      }
    }

  }
  free(tmp_row);

  return 0;
}

/* Solves A x = b, where T and perm contain the PLU factorisation of A. On input, x contains
 * b; on output, x contains the solution. Since PA = LU, we solve L U x = P b. */
void lu_pivot_solve(const struct DenseMatrix *T, const int *perm, double *x)
{
  /* TODO: 1) compute P b in an auxiliary array (malloc), entry i being b[perm[i]],
   *       2) copy it into x and free the auxiliary array, 3) call lu_solve.             */

  int n = T->n;
  double *aux_b = malloc(n * sizeof(*aux_b));

  for (int i = 0; i < n; i++){
    aux_b[i] = x[perm[i]];
  }

  memcpy(x, aux_b, n * sizeof(double));
  free(aux_b);

  lu_solve(T,x);

}

/* ======================================================================================
 * Part 3 (Exercise 6). Fill-in.
 * ====================================================================================== */

/* Number of entries of T with |T(i,j)| > TOL. */
int count_nonzeros(const struct DenseMatrix *T)
{
  /* TODO */

  int n = T->n;
  double *m_T = T->a;

  int zeros = 0;
  for(int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if(fabs(m_T[i * n + j]) > TOL){
        zeros++;
      }
    }
  }
  return zeros;
}

/* Arrow matrix (A already allocated, all entries 0): n on the diagonal and 1 in the
 * first row and the first column if first = 1, in the last row and the last column if
 * first = 0. */
void arrow_matrix(struct DenseMatrix *A, int first)
{
  /* TODO */
  int n = A->n;
  for(int i = 0; i < n; i++){
    if(first == 1){
      A->a[i] = 1;
      A->a[i*n] = 1;
    }else if(first == 0){
      A->a[(n - 1) * n + i] = 1;
      A->a[i * n + n - 1] = 1;
    }
    A->a[i * n + i] = n;
  }

}

/* ======================================================================================
 * main: add the lines given in each exercise of the sheet.
 * ====================================================================================== */

int main(void)
{
  /* Exercise 1 */
  printf("--- EX1 ---\n");
  double v[9] = {4, 2, 1, 2, 4, 2, 1, 2, 4};
  struct DenseMatrix A, T;
  dense_initialize(&A, 3); dense_set(&A, v); dense_copy(&T, &A);
  int ret = lu_decompose(&T);
  printf(" lu_decompose returns %d, T =\n", ret);
  dense_print(&T);

  /* Exercise 2 */
  printf("--- EX2 ---\n");

  double x[3] = {7, 8, 7};
  lu_solve(&T, x);
  print_vector("x", x, 3);
  dense_dispose(&A);
  dense_dispose(&T);

  printf("--- EX2.3 ---\n");
  int n_3 = 100;
  struct DenseMatrix A_3, T_3;

  dense_initialize(&A_3, n_3);
  random_dd_matrix(&A_3);

  dense_copy(&T_3, &A_3);


  double *x_3, *b_3;
  x_3 = malloc(n_3 * sizeof(double));
  b_3 = malloc(n_3 * sizeof(double));

  for(int i = 0; i < 100; i++){
    x_3[i] = 1.0;
    b_3[i] = 1.0;
  }

  lu_decompose(&T_3);
  lu_solve(&T_3, x_3);

  double res = residual(&A_3, x_3, b_3);
  printf("Residual (lf): %lf\n", res);
  printf("Residual (e): %e\n", res);

  /* Exercise 3 */
  printf("--- EX3 ---\n");

  printf(" %6s %14s %14s\n", "n", "factorise (s)", "solve (s)");
  for (int n = 100; n <= 400; n *= 2) {
    struct DenseMatrix B;
    dense_initialize(&B, n); random_dd_matrix(&B);
    double *y = malloc(n * sizeof(double));
    double t0 = seconds();
    lu_decompose(&B);
    double t1 = seconds();
    for (int r = 0; r < 100; ++r) { /* 100 solves: one is too fast to measure */
      for (int i = 0; i < n; ++i) y[i] = 1.0;
        lu_solve(&B, y);
    }
      double t2 = seconds();
      printf(" %6d %14.4f %14.6f\n", n, t1 - t0, (t2 - t1) / 100);
      free(y); dense_dispose(&B);
  }

  /* Exercise 4 */
  printf("--- EX4 ---\n");
  
  double v1[4] = {0, 1, 1, 0};
  dense_initialize(&T, 2); dense_set(&T, v1);
  ret = lu_decompose(&T);
  printf(" [0 1; 1 0]: lu_decompose returns %d\n", ret);
  dense_dispose(&T);
  double eps = 1e-20, v2[4] = {eps, 1, 1, 1}, x2[2] = {1, 2};
  dense_initialize(&T, 2); dense_set(&T, v2);
  lu_decompose(&T); lu_solve(&T, x2);
  print_vector("[eps 1; 1 1], without pivoting: x", x2, 2);
  dense_dispose(&T);


  /* Exercise 5 */
  printf("--- EX5 ---\n");

  double v3[9] = {1, 2, 3, 2, 4, 5, 3, 5, 6};
  int perm[3];
  dense_initialize(&A, 3); dense_set(&A, v3); dense_copy(&T, &A);
  ret = lu_decompose(&T);
  printf(" without pivoting: lu_decompose returns %d\n", ret);
  dense_dispose(&T); dense_copy(&T, &A);
  ret = lu_pivot(&T, perm);
  printf(" with pivoting: lu_pivot returns %d, perm = %d %d %d, T =\n", ret, perm[0], perm[1], perm[2]);
  dense_print(&T);
  double x3[3] = {6, 11, 14};
  lu_pivot_solve(&T, perm, x3);
  print_vector("x", x3, 3);

  printf("--- EX5.3 ---\n");
  double eps_2 = 1e-20, v2_2[4] = {eps_2, 1, 1, 1}, x2_2[2] = {1, 2};
  int perm_2[2];
  dense_initialize(&T, 2); dense_set(&T, v2_2);
  lu_decompose(&T);
  ret = lu_pivot(&T, perm_2);
  printf(" with pivoting: lu_pivot returns %d, perm = %d %d, T =\n", ret, perm_2[0], perm_2[1]);
  lu_pivot_solve(&T, perm_2, x2_2);
  print_vector("[eps 1; 1 1], without pivoting: x", x2_2, 2);
  dense_dispose(&T);

  printf("--- EX5.4 ---\n");
  int n5 = 100;
  double b5[100];
  double x5[100];
  int perm5[100];
  for (int i = 0; i < n5; i++) {
    b5[i] = 1.0;
    x5[i] = 1.0;
  }

  struct DenseMatrix A5;
  dense_initialize(&A5, n5);
  random_matrix(&A5);

  /* Without pivoting */
  dense_copy(&T, &A5);
  lu_decompose(&T);
  lu_solve(&T, x5);
  double res5 = residual(&A5, x5, b5);
  printf("residual without pivoting for n = %d : %e\n", n5, res5);
  dense_dispose(&T);

  /* With pivoting */
  dense_copy(&T, &A5);
  for (int i = 0; i < n5; i++) {
    x5[i] = 1.0;
  }
  ret = lu_pivot(&T, perm5);
  lu_pivot_solve(&T, perm5, x5);
  res5 = residual(&A5, x5, b5);
  printf("residual with pivoting for n = %d : %e\n", n5, res5);

  dense_dispose(&T);
  dense_dispose(&A5);

  /* Exercise 6 */
  printf("--- EX6 ---\n");
  for (int first = 1; first >= 0; --first) {
    dense_initialize(&A, 8);
    arrow_matrix(&A, first);
    dense_print(&A);
    int before = count_nonzeros(&A);
    lu_decompose(&A);
    printf("after lu \n");
    dense_print(&A);
    printf(" first = %d: %d nonzeros in A, %d in T\n", first, before,
    count_nonzeros(&A));
    dense_dispose(&A);
  }



  return 0;
}
