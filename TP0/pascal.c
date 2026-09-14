#include <stdio.h>

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n must be a positive integer.\n");
        return 1;
    }

    long long A[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {

            if (j == 0 || j == i) {
                A[i][j] = 1;
            }
            else {
                A[i][j] = A[i-1][j-1] + A[i-1][j];
            }

            printf("%lld ", A[i][j]);
        }

        printf("\n");
    }

    return 0;
}

