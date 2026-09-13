#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        printf("n must be positive.\n");
        return 1;
    }

    long long *A = malloc(n * sizeof(long long));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {

        for (int j = i; j >= 0; j--) {
            if (j == 0 || j == i) {
                A[j] = 1;
            } else {
                A[j] = A[j - 1] + A[j];
            }
        }

        for (int j = 0; j <= i; j++) {
            printf("%lld ", A[j]);
        }

        printf("\n");
    }

    free(A);

    return 0;
}