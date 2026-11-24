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
  for(int p = 0;  p < n - 1; p++){
    if(T->a[p * n + p] == 0) return -1;

    for(int r = p + 1; r < n; r++){
      T->a[r * n + p] /= T->a[p * n + p];

      for(int c = p + 1; c < n; c++){
        T->a[r * n + c] = T->a[r * n + c] - T->a[r * n + p] * T->a[p * n + c];
      }
    }
  }

  if(T->a[(n-1) * n + n-1] == 0) return -1;

  return 0;
}

/* Solves A x = b, where T contains the LU factorisation of A (Algorithm 2.3).
 * On input, x contains b; on output, x contains the solution. */
void lu_solve(const struct DenseMatrix *T, double *x)
{
  int n = T->n;

  //L solve
  for(int j = 0; j < n; j++){
    for(int k = 0; k < j; k++){
      x[j] -= T->a[j * n + k] * x[k];
    }
  }

  //U solve
  for(int j = n - 1; j >= 0; j--){

    for(int k = j + 1; k < n; k++){
      x[j] -= T->a[j * n + k] * x[k];
    }

    x[j] /= T->a[j * n + j];
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
  int n = T->n;
  for(int i = 0; i < n; i++){
    perm[i] = i;
  }

  for(int q = 0; q < n - 1; q++){
    double r_max = absval(T->a[q*n + q]);
    int r = q;
    for(int j = q + 1; j < n; j++){
      if(absval(T->a[j*n + q]) > r_max) {r_max = absval(T->a[j*n + q]); r = j;}
    }

    if(r_max < TOL) return -1;

    if(r != q){
      for(int i = 0; i < n; i++){
        double tmp = T->a[r*n + i];
        T->a[r*n + i] = T->a[q*n + i];
        T->a[q*n + i] = tmp;
      }
    }

    int tmp = perm[q];
    perm[q] = perm[r];
    perm[r] = tmp;

    for(int r = q + 1; r < n; r++){
      T->a[r * n + q] /= T->a[q * n + q];

      for(int c = q + 1; c < n; c++){
        T->a[r * n + c] = T->a[r * n + c] - T->a[r * n + q] * T->a[q * n + c];
      }
    }
  }

  if(absval(T->a[(n-1)*n + n-1]) < TOL) return -1;

  return 0;
}

/* Solves A x = b, where T and perm contain the PLU factorisation of A. On input, x contains
 * b; on output, x contains the solution. Since PA = LU, we solve L U x = P b. */
void lu_pivot_solve(const struct DenseMatrix *T, const int *perm, double *x)
{
   double *b = malloc(T->n* sizeof(double));
   for(int i = 0; i < T->n; i++) b[i] = x[perm[i]];
   for(int i = 0; i < T->n; i++) x[i] = b[i];
   free(b);

   lu_solve(T, x);
}

/* ======================================================================================
 * Part 3 (Exercise 6). Fill-in.
 * ====================================================================================== */

/* Number of entries of T with |T(i,j)| > TOL. */
int count_nonzeros(const struct DenseMatrix *T)
{
  int res = 0;
  for(int i = 0; i < T->n; i++){
    for(int j = 0; j < T->n; j++){
      if(absval(T->a[i*T->n + j]) > TOL) res++;
    }
  }
  return res;
}

/* Arrow matrix (A already allocated, all entries 0): n on the diagonal and 1 in the
 * first row and the first column if first = 1, in the last row and the last column if
 * first = 0. */
void arrow_matrix(struct DenseMatrix *A, int first)
{
  int n = A->n;
  for(int i = 0; i < n; i++){
    if(first == 1){
      A->a[i*n] = 1; 
      A->a[i] = 1; 
    }else{
      A->a[i*n + n - 1] = 1;
      A->a[(n-1)*n + i] = 1;
    }

    A->a[i*n + i] = n;
  }
}

int main(void)
{
  struct DenseMatrix A, T;
  int ret;
  double b[100], y[100];

  printf("==================================================================\n");
  printf(" Exercise 1 -- LU factorisation without pivoting\n");
  printf("==================================================================\n");
  double v[9] = {4, 2, 1, 2, 4, 2, 1, 2, 4};
  dense_initialize(&A, 3); dense_set(&A, v); dense_copy(&T, &A);
  printf(" A =\n");
  dense_print(&A);
  ret = lu_decompose(&T);
  printf(" lu_decompose returns %d\n", ret);
  printf(" T = L\\U =\n");
  dense_print(&T);

  printf("\n==================================================================\n");
  printf(" Exercise 2 -- Solving A x = b with LU\n");
  printf("==================================================================\n");
  double x[3] = {7, 8, 7};
  print_vector("b", x, 3);
  lu_solve(&T, x);
  print_vector("x", x, 3);
  printf("  residual max|Ax - b| = %.3e\n", residual(&A, x, (double[]){7, 8, 7}));
  dense_dispose(&T);
  dense_dispose(&A);

  /* Ex 2, Q2. b = (7, 8, 7) is just the sum of the rows of A (4+2+1, 2+4+2, 1+2+4),
   * so A*(1,1,1) = b and x = (1,1,1) was expected. */

  printf("\n -- Random diagonally dominant matrix, n = 100, b = (1,...,1) --\n");
  for (int i = 0; i < 100; i++) { b[i] = 1.0; y[i] = 1.0; }
  dense_initialize(&A, 100);
  random_dd_matrix(&A);
  dense_copy(&T, &A);
  ret = lu_decompose(&T);
  printf("  lu_decompose returns %d\n", ret);
  lu_solve(&T, y);
  printf("  residual max|Ax - b| = %.3e\n", residual(&A, y, b));
  dense_dispose(&T);
  dense_dispose(&A);

  /* Ex 2, Q3. On each row |a_ii| >= n+1 - 1 = n, while the other n-1 entries sum to at
   * most n-1 in absolute value: the matrix is strictly diagonally dominant, so it is
   * invertible. Its leading submatrices are also strictly diagonally dominant, hence
   * invertible too, and that is exactly the condition for LU to exist. */

  printf("\n==================================================================\n");
  printf(" Exercise 3 -- Computing times\n");
  printf("==================================================================\n");
  printf(" %6s %14s %14s\n", "n", "factorise (s)", "solve (s)");
  for (int n = 100; n <= 1600; n *= 2) {
    struct DenseMatrix B;
    dense_initialize(&B, n); random_dd_matrix(&B);
    double *z = malloc(n * sizeof(double));

    double t0 = seconds();
    lu_decompose(&B);
    double t1 = seconds();
    for (int r = 0; r < 100; ++r) { // 100 solves: one is too fast to measure
      for (int i = 0; i < n; ++i) z[i] = 1.0;
      lu_solve(&B, z);
    }
    double t2 = seconds();

    printf(" %6d %14.4f %14.6f\n", n, t1 - t0, (t2 - t1) / 100);
    free(z); dense_dispose(&B);
  }

  /* Ex 3, Q1. When n doubles, the factorisation time is multiplied by about 8 = 2^3 and
   * the solve time by about 4 = 2^2, as expected from the costs (2/3)n^3 and 2n^2
   * (for small n the times are a bit noisy).
   * From n = 1600 (about 5 s to factorise, 0.006 s to solve):
   *   n = 10^4: x6.25 in n -> factorise ~ 5 * 6.25^3 ~ 1200 s (20 min), solve ~ 0.25 s
   *   n = 10^5: x62.5 in n -> factorise ~ 5 * 62.5^3 ~ 1.2e6 s (2 weeks), solve ~ 25 s
   * and for n = 10^5 the dense matrix alone would take 10^10 * 8 bytes = 80 GB. */

  /* Ex 3, Q2. The factorisation only depends on A, not on b. So we factorise once
   * ((2/3)n^3) and then each new b only costs two triangular solves (2n^2): for k
   * right-hand sides that is (2/3)n^3 + 2kn^2 instead of k*(2/3)n^3. Here, for
   * n = 1600, a solve is several hundred times cheaper than a factorisation. */

  printf("\n==================================================================\n");
  printf(" Exercise 4 -- Limits of LU without pivoting\n");
  printf("==================================================================\n");
  double v1[4] = {0, 1, 1, 0};
  dense_initialize(&T, 2); dense_set(&T, v1);
  ret = lu_decompose(&T);
  printf(" A = [0 1; 1 0]:   lu_decompose returns %d\n", ret);
  dense_dispose(&T);

  double eps = 1e-20, v2[4] = {eps, 1, 1, 1}, x2[2] = {1, 2};
  dense_initialize(&T, 2); dense_set(&T, v2);
  lu_decompose(&T); lu_solve(&T, x2);
  printf(" A = [eps 1; 1 1], eps = %g, b = (1, 2):\n", eps);
  print_vector("without pivoting: x", x2, 2);
  dense_dispose(&T);

  /* Ex 4, Q1. LU without pivoting exists only if all the leading principal minors are
   * nonzero. Here the first one is a_11 = 0, so the very first pivot is zero, even
   * though det A = -1 != 0.
   *
   * Ex 4, Q2. Exact solution: x1 = 1/(1-eps), x2 = (1-2eps)/(1-eps), so x ~ (1, 1).
   * By hand: l21 = 1/eps = 1e20 and u22 = 1 - 1e20. In double precision the 1 is
   * lost, u22 = -1e20. Same for y2 = 2 - 1e20 = -1e20, so x2 = 1 but then
   * x1 = (1 - x2)/eps = 0 instead of 1: the information of the second row has been
   * lost.
   *
   * Ex 4, Q3. A test |Tpp| < 1e-12 is not scale invariant: 1e-13 * I is a good
   * matrix, but every pivot would be rejected. Multiplying A by a constant should not
   * change the answer, so in lu_decompose we only stop when we really cannot divide,
   * i.e. Tpp = 0. */

  printf("\n==================================================================\n");
  printf(" Exercise 5 -- LU with partial pivoting\n");
  printf("==================================================================\n");
  double v3[9] = {1, 2, 3, 2, 4, 5, 3, 5, 6};
  int perm[3];
  dense_initialize(&A, 3); dense_set(&A, v3); dense_copy(&T, &A);
  printf(" A =\n");
  dense_print(&A);
  ret = lu_decompose(&T);
  printf(" without pivoting: lu_decompose returns %d\n", ret);
  dense_dispose(&T); dense_copy(&T, &A);
  ret = lu_pivot(&T, perm);
  printf(" with pivoting:    lu_pivot returns %d, perm = (%d, %d, %d)\n", ret,
         perm[0], perm[1], perm[2]);
  printf(" T = L\\U =\n");
  dense_print(&T);
  double x3[3] = {6, 11, 14};
  print_vector("b", x3, 3);
  lu_pivot_solve(&T, perm, x3);
  print_vector("x", x3, 3);
  dense_dispose(&T);
  dense_dispose(&A);

  printf("\n -- A = [eps 1; 1 1], eps = %g, b = (1, 2) --\n", eps);
  dense_initialize(&T, 2); dense_set(&T, v2);
  int perm2[2];
  x2[0] = 1; x2[1] = 2;
  lu_pivot(&T, perm2); lu_pivot_solve(&T, perm2, x2);
  print_vector("with pivoting: x", x2, 2);
  dense_dispose(&T);

  /* Ex 5, Q3. lu_decompose fails because after the first step T(2,2) = 4 - 2*2 = 0:
   * the leading 2x2 minor det [1 2; 2 4] = 0, even though A is invertible.
   * With pivoting on [eps 1; 1 1] the rows are swapped, the pivot is 1 and the
   * multiplier is eps (<= 1), so nothing is lost and we get x = (1, 1). */

  printf("\n -- Random matrix (not diagonally dominant), n = 100, b = (1,...,1) --\n");
  dense_initialize(&A, 100); random_matrix(&A);

  dense_copy(&T, &A);
  for (int i = 0; i < 100; i++) { b[i] = 1.0; y[i] = 1.0; }
  ret = lu_decompose(&T); lu_solve(&T, y);
  printf("  without pivoting: returns %2d, residual = %.3e\n", ret, residual(&A, y, b));
  dense_dispose(&T);

  dense_copy(&T, &A);
  int perm3[100];
  for (int i = 0; i < 100; i++) y[i] = 1.0;
  ret = lu_pivot(&T, perm3); lu_pivot_solve(&T, perm3, y);
  printf("  with pivoting:    returns %2d, residual = %.3e\n", ret, residual(&A, y, b));
  dense_dispose(&T); dense_dispose(&A);

  /* Ex 5, Q4. This time the matrix is not diagonally dominant, so the pivots can be
   * small and the multipliers large, which amplifies the rounding errors. Here LU
   * without pivoting still works, but the residual is about 200 times bigger (~2e-11
   * against ~1e-13), and with another random matrix it could be much worse. With
   * partial pivoting |l_ij| <= 1 and the residual stays close to machine precision. */

  printf("\n==================================================================\n");
  printf(" Exercise 6 -- Fill-in (arrow matrices, n = 8)\n");
  printf("==================================================================\n");
  for (int first = 1; first >= 0; --first) {
    dense_initialize(&A, 8); arrow_matrix(&A, first);
    printf("\n Arrow in the %s row/column (first = %d), A =\n",
           first ? "first" : "last", first);
    dense_print(&A);
    int before = count_nonzeros(&A);
    lu_decompose(&A);
    printf(" T = L\\U =\n");
    dense_print(&A);
    printf(" nonzeros: %d in A, %d in T\n", before, count_nonzeros(&A));
    dense_dispose(&A);
  }

  /* Ex 6, Q2. first = 1: row 0 is full and every row has a nonzero in column 0. So at
   * the first step each row i gets row 0 times l_i0 subtracted, and becomes full:
   * after one step the whole matrix is dense, hence 64 nonzeros.
   * first = 0: at step p the only nonzero below the pivot is in the last row, and
   * row p only has entries in columns p and n-1, so the only entry that changes is
   * T(n-1,n-1). No fill-in at all, 22 nonzeros.
   *
   * Ex 6, Q3. It is the same system, only the unknowns are numbered differently, and
   * yet one ordering gives a full matrix and the other no fill-in. So for a large
   * sparse matrix the memory and the cost of LU depend mostly on the ordering of the
   * unknowns (how much fill-in it creates), not only on the number of nonzeros of A. */

  return 0;
}
