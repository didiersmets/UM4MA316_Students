
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);

    int **A = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                A[i][j] = 1;
            } else {
                A[i][j] = A[i - 1][j - 1] + A[i - 1][j];
            }
            printf("%4d", A[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}
