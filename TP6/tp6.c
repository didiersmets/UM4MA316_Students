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
struct DenseMatrix
{
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
  if (dense_initialize(B, A->n))
    return -1;
  for (int k = 0; k < A->n * A->n; ++k)
    B->a[k] = A->a[k];
  return 0;
}

/* Fills A (already allocated) with the n*n values of the array v, row after row. */
void dense_set(struct DenseMatrix *A, const double *v)
{
  for (int k = 0; k < A->n * A->n; ++k)
    A->a[k] = v[k];
}

void dense_print(const struct DenseMatrix *A)
{
  for (int i = 0; i < A->n; ++i)
  {
    printf("   ");
    for (int j = 0; j < A->n; ++j)
      printf(" %8.4g", A->a[i * A->n + j]);
    printf("\n");
  }
}

void print_vector(const char *name, const double *x, int n)
{
  printf("  %s =", name);
  for (int i = 0; i < n; ++i)
    printf(" %.6g", x[i]);
  printf("\n");
}

/* max_i |(Ax - b)_i| */
double residual(const struct DenseMatrix *A, const double *x, const double *b)
{
  int n = A->n;
  double r = 0.0;
  for (int i = 0; i < n; ++i)
  {
    double s = -b[i];
    for (int j = 0; j < n; ++j)
      s += A->a[i * n + j] * x[j];
    if (absval(s) > r)
      r = absval(s);
  }
  return r;
}

/* Random matrix with entries in [-1, 1]. */
void random_matrix(struct DenseMatrix *A)
{
  for (int k = 0; k < A->n * A->n; ++k)
    A->a[k] = 2.0 * rand() / RAND_MAX - 1.0;
}

/* Random matrix with entries in [-1, 1], plus n+1 on the diagonal: it is strictly diagonally
 * dominant, hence it admits an LU factorisation (Proposition 2.4). */
void random_dd_matrix(struct DenseMatrix *A)
{
  int n = A->n;
  random_matrix(A);
  for (int i = 0; i < n; ++i)
    A->a[i * n + i] += n + 1;
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
  /* TODO: translate Algorithm 2.2 into three nested loops (entry (i,j) is T->a[i*n + j]):
   *   for p = 0, ..., n-2:
   *     if T(p,p) == 0, return -1             (zero pivot: no LU without pivoting)
   *     for each row i > p:
   *       T(i,p) = T(i,p) / T(p,p)            (multiplier, stored in place of the zero)
   *       for each column j > p:
   *         T(i,j) = T(i,j) - T(i,p) * T(p,j)
   * Then check the last pivot T(n-1,n-1) in the same way, and return 0.                */
  int n = T->n;
  for (int p = 0; p < n - 1; p++)
  {
    if (T->a[p * n + p] == 0)
      return -1;
    for (int i = p + 1; i < n; i++) // this is the row in a normal scheme matrix we convert later
    {
      T->a[i * n + p] = T->a[i * n + p] / T->a[p * n + p];
      for (int j = p + 1; j < n; j++)
      {
        T->a[i * n + j] = T->a[i * n + j] - (T->a[i * n + p] * T->a[p * n + j]);
      }
    }
  }
  if (T->a[(n - 1) * n + (n - 1)] == 0)
    return -1;
  return 0;
}

/* Solves A x = b, where T contains the LU factorisation of A (Algorithm 2.3).
 * On input, x contains b; on output, x contains the solution. */
void lu_solve(const struct DenseMatrix *T, double *x)
{
  /* TODO: 1) forward substitution with L (ones on the diagonal),
   *       2) backward substitution with U.
   */
  int n = T->n;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      x[i] = x[i] - T->a[i * n + j] * x[j];
    }
  }
  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = i + 1; j < n; j++)
    {
      x[i] = (x[i] - T->a[i * n + j] * x[j]);
    }
    x[i] /= (T->a[i * n + i]);
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
- |T(q,p)|; if it is < TOL, return -1; swap rows p and q of T (all columns) and
- perm[p], perm[q]; then eliminate below the pivot as in lu_decompose.               */

  int n = T->n;
  for (int i = 0; i < n; i++) perm[i] = i;

  for (int p = 0; p < n - 1; p++)
  {
    //perform the search 
    int q_max = p;
    for (int q = p; q < n; q++){
      if (absval(T->a[q*n+p]) > absval(T->a[q_max*n + p])) q_max = q;
    }
    if (absval(T->a[q_max*n + p]) < TOL) return -1;

    //perform the swap here q_max and p 
    for (int column = 0; column < n; column++){
      double temp = T->a[p*n+column];
      T->a[p*n+column] = T->a[q_max*n + column];
      T->a[q_max*n + column] = temp;
    }
    int temp_perm = perm[p];
    perm[p] = perm[q_max];
    perm[q_max] = temp_perm;

    //then we eliminate exactly like lu decompose 
    for (int i = p + 1; i < n; i++) 
    {
      T->a[i * n + p] = T->a[i * n + p] / T->a[p * n + p];
      for (int j = p + 1; j < n; j++)
      {
        T->a[i * n + j] = T->a[i * n + j] - (T->a[i * n + p] * T->a[p * n + j]);
      }
    }
  }
  if (absval(T->a[(n - 1) * n + (n - 1)]) < TOL)
    return -1;
  return 0;
}


/* Solves A x = b, where T and perm contain the PLU factorisation of A. On input, x contains
 * b; on output, x contains the solution. Since PA = LU, we solve L U x = P b. */
void lu_pivot_solve(const struct DenseMatrix *T, const int *perm, double *x)
{
  /* TODO: 1) compute P b in an auxiliary array (malloc), entry i being b[perm[i]],
   *       2) copy it into x and free the auxiliary array, 3) call lu_solve.             */
  int n = T->n;
  double *Pb = malloc(sizeof(double)*n);
  if(!Pb) return;
  for (int i = 0; i<n; i++){
    Pb[i] = x[perm[i]];
  }
  for (int i = 0; i<n; i++){
    x[i]=Pb[i];
  }
  free(Pb);
  lu_solve(T,x);
}

/* ======================================================================================
 * Part 3 (Exercise 6). Fill-in.
 * ====================================================================================== */

/* Number of entries of T with |T(i,j)| > TOL. */
int count_nonzeros(const struct DenseMatrix *T)
{
  int n = T->n;
  int count = 0;
  for(int i = 0; i<n; i++){
    for(int j = 0; j<n; j++){
      if(absval(T->a[i*n+j])>TOL) count++;
    }
  }
  return count;
}

/* Arrow matrix (A already allocated, all entries 0): n on the diagonal and 1 in the
 * first row and the first column if first = 1, in the last row and the last column if
 * first = 0. */
void arrow_matrix(struct DenseMatrix *A, int first)
{
  int n = A->n;
  if (first){
    for(int i = 1; i<n; i++){
      A->a[i] = 1;
    }
    for(int i = 1; i<n; i++){
      A->a[i*n] = 1;
    }
  }
  else{
    for(int i = 0; i<n-1; i++){
      A->a[(n-1)*n+i] = 1;
    }
    for(int i = 0; i<n-1; i++){
      A->a[i*n + (n-1)] = 1;
    }
  }
  for(int i = 0; i<n; i++){
    A->a[i*n+i]=n;
  }
}

/* ======================================================================================
 * main: add the lines given in each exercise of the sheet.
 * ====================================================================================== */

int main(void)
{
  double v[9] = {4, 2, 1, 2, 4, 2, 1, 2, 4};
  struct DenseMatrix A, T;
  dense_initialize(&A, 3);
  dense_set(&A, v);
  dense_copy(&T, &A);
  int ret = lu_decompose(&T);
  printf(" lu_decompose returns %d, T =\n", ret);
  dense_print(&T);

  double x[3] = {7, 8, 7};
  lu_solve(&T, x);
  print_vector("x", x, 3);

  dense_dispose(&A);
  dense_dispose(&T);

  int n = 100;
  struct DenseMatrix B, LU;
  dense_initialize(&B, n);
  random_dd_matrix(&B);
  dense_copy(&LU, &B);
  int check = lu_decompose(&LU);
  printf(" lu_decompose returns %d, LU =\n", check);

  double b[n];
  double y[n];
  for (int i = 0; i < n; i++)
  {
    b[i] = 1;
    y[i] = 1;
  }

  lu_solve(&LU, y);

  double resi = residual(&B, y, b);

  printf("residual: %e\n", resi);

  dense_dispose(&B);
  dense_dispose(&LU);

  printf(" %6s %14s %14s\n", "n", "factorise (s)", "solve (s)");
  for (int n = 100; n <= 1600; n *= 2)
  {
    struct DenseMatrix B;
    dense_initialize(&B, n);
    random_dd_matrix(&B);
    double *y = malloc(n * sizeof(double));
    double t0 = seconds();
    lu_decompose(&B);
    double t1 = seconds();
    for (int r = 0; r < 100; ++r)
    { /* 100 solves: one is too fast to measure */
      for (int i = 0; i < n; ++i)
        y[i] = 1.0;
      lu_solve(&B, y);
    }
    double t2 = seconds();
    printf(" %6d %14.4f %14.6f\n", n, t1 - t0, (t2 - t1) / 100);
    free(y);
    dense_dispose(&B);
  }

  /*
   * Exercise 1/2 (1): 
   * Expected x = (1, 1, 1)^T.
   * Each row of A sums to b_i (4+2+1=7, 2+4+2=8, 1+2+4=7), so A * (1, 1, 1)^T = b.
   * Since A is strictly diagonally dominant (hence invertible), x = (1, 1, 1)^T
   * is the unique solution.
   */

  /*
   * Exercise 1/2 (3): Invertibility & LU existence for random_dd_matrix.
   * - Off-diagonal entries lie in [-1, 1], so sum_{j != i} |a_ij| <= n - 1.
   * - Adding (n + 1) to a_ii in [-1, 1] gives |a_ii| >= n > n - 1 >= sum_{j != i} |a_ij|.
   * - Strict diagonal dominance guarantees invertibility and
   *   carries over to all leading principal submatrices A_k, ensuring det(A_k) != 0
   *   so A = LU exists without pivoting (Proposition 2.4).
   * - Without +(n + 1): a continuous random matrix is still invertible almost surely
   *   (det(A) = 0 has measure zero), but LU without pivoting can fail or lose
   *   stability if a leading principal minor is zero or near-zero.
   */

  /*
   * Exercise 3 (1): Scaling & runtime estimates.
   * - Doubling n multiplies factorisation time by ~8 (2^3, matching (2/3)n^3 flops)
   *   and solve time by ~4 (2^2, matching 2n^2 flops).
   * - From n = 1600 baseline (T_fact ~ 3.86 s, T_solve ~ 9.35e-3 s):
   *   * n = 10^4 (6.25x): T_fact ~ 3.86 * 6.25^3 ~ 942 s (~15.7 min),
   *                       T_solve ~ 9.35e-3 * 6.25^2 ~ 0.365 s.
   *   * n = 10^5 (62.5x): T_fact ~ 9.4e5 s (~10.9 days),
   *                       T_solve ~ 36.5 s.
   *
   * Exercise 3 (2): Reusing LU for multiple right-hand sides.
   * - L and U depend only on A, not on b. Factorising once in O(n^3) and solving
   *   for k right-hand sides via forward/backward substitution reduces total cost
   *   from O(k * n^3) to O(n^3 + k * n^2).
   */

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

  /*
   * Exercise 4 (1): [0 1; 1 0] returns -1 despite being invertible (det = -1).
   * LU without pivoting exists iff all leading principal minors are non-zero.
   * Here det(A_1) = a_00 = 0, causing an immediate zero pivot at p = 0.
   *
   * Exercise 4 (2): [eps 1; 1 1] x = [1; 2] with eps = 1e-20.
   * - Exact solution: x_1 = 1/(1 - eps) ~ 1, x_2 = (1 - 2*eps)/(1 - eps) ~ 1.
   * - Hand LU: l_21 = 1/eps = 1e20, u_22 = 1 - 1e20.
   * - In IEEE 754 double (~16 digits, eps_mach ~ 2.2e-16), fl(1 - 1e20) = -1e20
   *   and fl(2 - 1e20) = -1e20 (the 1 and 2 are swamped), giving x_2 = -1e20/-1e20 = 1
   *   and x_1 = (1 - 1)/1e-20 = 0 instead of (1, 1).
   *
   * Exercise 4 (3): Why test T(p,p) == 0 instead of |T(p,p)| < 1e-12?
   * - Pivot magnitude is scale-dependent: A = 1e-13 * I is perfectly conditioned
   *   (kappa(A) = 1, exact LU with L = I, U = 1e-13 * I), yet |T(p,p)| = 1e-13 < 1e-12
   *   would falsely reject it. Instability depends on large multipliers |T(i,p)/T(p,p)|,
   *   not absolute scale.
   */

  /* Exercise 5 (3): 3x3 test and Exercise 4 matrices with partial pivoting */
  double v3[9] = {1, 2, 3, 2, 4, 5, 3, 5, 6};
  int perm[3];
  dense_initialize(&A, 3); dense_set(&A, v3); dense_copy(&T, &A);
  ret = lu_decompose(&T);
  printf(" without pivoting: lu_decompose returns %d\n", ret);
  dense_dispose(&T); dense_copy(&T, &A);
  ret = lu_pivot(&T, perm);
  printf(" with pivoting: lu_pivot returns %d, perm = %d %d %d, T =\n", ret,
         perm[0], perm[1], perm[2]);
  dense_print(&T);
  double x3[3] = {6, 11, 14};
  lu_pivot_solve(&T, perm, x3);
  print_vector("x", x3, 3);
  dense_dispose(&T);
  dense_dispose(&A);

  /* Second matrix of Exercise 4 solved WITH partial pivoting */
  int perm2[2];
  double x2_piv[2] = {1, 2};
  dense_initialize(&T, 2); dense_set(&T, v2);
  lu_pivot(&T, perm2);
  lu_pivot_solve(&T, perm2, x2_piv);
  print_vector("[eps 1; 1 1], with pivoting: x", x2_piv, 2);
  dense_dispose(&T);

  /*
   * Exercise 5 (3) Theory:
   * - Why lu_decompose fails on A = [1 2 3; 2 4 5; 3 5 6]:
   *   The 2x2 leading principal minor is det([1 2; 2 4]) = 4 - 4 = 0.
   *   At step p = 0, eliminating row 1 gives T(1,1) = 4 - (2/1)*2 = 0,
   *   causing a zero-pivot breakdown at step p = 1 even though det(A) = -1 != 0.
   * - With partial pivoting on [eps 1; 1 1]:
   *   Rows 0 and 1 swap (perm = [1, 0]), giving pivot 1 and multiplier l_21 = eps = 1e-20.
   *   Then u_22 = 1 - 1e-20*1 = 1 in double precision (no swamping), yielding x = (1, 1).
   */

  /* Exercise 5 (4): n = 100 random_matrix (no diagonal dominance) with vs without pivoting */
  int n100 = 100;
  struct DenseMatrix R, R_lu, R_plu;
  int *perm100 = malloc(n100 * sizeof(int));
  double *b100 = malloc(n100 * sizeof(double));
  double *x_nopiv = malloc(n100 * sizeof(double));
  double *x_piv = malloc(n100 * sizeof(double));

  dense_initialize(&R, n100);
  random_matrix(&R);
  dense_copy(&R_lu, &R);
  dense_copy(&R_plu, &R);

  for (int i = 0; i < n100; i++) {
    b100[i] = 1.0;
    x_nopiv[i] = 1.0;
    x_piv[i] = 1.0;
  }

  int ret_nopiv = lu_decompose(&R_lu);
  if (ret_nopiv == 0) {
    lu_solve(&R_lu, x_nopiv);
    printf(" random_matrix (n=100) without pivoting residual: %e\n", residual(&R, x_nopiv, b100));
  } else {
    printf(" random_matrix (n=100) without pivoting failed (zero pivot)\n");
  }

  int ret_piv = lu_pivot(&R_plu, perm100);
  if (ret_piv == 0) {
    lu_pivot_solve(&R_plu, perm100, x_piv);
    printf(" random_matrix (n=100) with pivoting residual:    %e\n", residual(&R, x_piv, b100));
  }

  free(perm100); free(b100); free(x_nopiv); free(x_piv);
  dense_dispose(&R); dense_dispose(&R_lu); dense_dispose(&R_plu);

  /*
   * Exercise 5 (4) Theory (cf. Exercise 2, Question 3):
   * - Without diagonal dominance, random_matrix is invertible almost surely, so
   *   lu_decompose usually succeeds (zero pivots have probability 0), BUT intermediate
   *   pivots can be arbitrarily small relative to remaining entries.
   * - Small pivots produce large multipliers |l_ip| >> 1, amplifying floating-point
   *   roundoff errors and giving a noticeably larger residual (typically ~1e-12 to 1e-10).
   * - Partial pivoting (PA = LU) bounds all multipliers by |l_ip| <= 1, preventing
   *   error amplification and keeping the residual near machine precision (~1e-15 to 1e-14).
   */


  /* Exercise 6: Fill-in on arrow matrices */
  for (int first = 1; first >= 0; --first) {
    dense_initialize(&A, 8);
    arrow_matrix(&A, first);
    dense_print(&A);
    int before = count_nonzeros(&A);
    lu_decompose(&A);
    printf(" first = %d: %d nonzeros in A, %d in T\n", first, before,
           count_nonzeros(&A));
    dense_dispose(&A);
  }

  /*
   * Exercise 6 (2): Why first = 1 produces complete fill-in (64 nonzeros in T):
   * - Both matrices start with 3n - 2 = 22 nonzeros.
   * - For first = 1, step p = 0 eliminates column 0 using row 0: every row i >= 1
   *   has multiplier l_{i,0} = 1/n != 0 and subtracts (1/n) * row_0 from row_i.
   * - Because row 0 is completely dense (all 1s in columns j >= 1), every zero entry
   *   A(i, j) (i, j >= 1, i != j) is updated to 0 - (1/n)*1 = -1/n != 0, turning
   *   the entire (n-1)x(n-1) trailing submatrix dense at step p = 0 (n^2 = 64 nonzeros).
   * - For first = 0, columns 0..n-2 have no off-diagonal entries below the diagonal
   *   (l_{i,p} = 0 for p < n - 1), so zero fill-in occurs (T keeps 22 nonzeros).
   *
   * Exercise 6 (3): What governs memory and cost of a sparse direct solver:
   * - Reordering the unknowns (P A P^T) dramatically changes fill-in during LU.
   * - Memory and flop count of a sparse direct solver are governed not just by the
   *   initial number of nonzeros in A, but by the amount of fill-in created in L and U,
   *   which depends critically on the ordering of the unknowns (e.g., minimum degree
   *   or nested dissection orderings).
   */

  return 0;
}
