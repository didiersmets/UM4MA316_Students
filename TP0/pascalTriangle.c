#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int n = atoi(argv[1]);

    int A[n][n];

    if(n>=0){
         A[0][0] = 1;
        printf("1\n");
        
        for (int i = 1; i < n; i++) {
            A[i][0] = 1;
            printf("1 ");

            for (int j = 1; j < i; j++) {
                A[i][j] = A[i-1][j-1] + A[i-1][j];
                printf("%d ", A[i][j]);
            }

            A[i][i] = 1;
            printf("1\n");
        }

    }
    return 0;
}