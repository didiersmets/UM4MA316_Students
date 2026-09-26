#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("no integer provided in the command line\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if(n <= 0) {
        printf("insert a positive integer\n");
        return 1;
    }

    int *A = malloc(n*n*sizeof(int));

    if(n>=0){
         A[0] = 1;
        printf("1\n");
        
        for (int i = 1; i < n; i++) {
            A[i*n + 0] = 1;
            printf("1 ");

            for (int j = 1; j < i; j++) {
                A[i*n + j] = A[(i-1)*n + j-1] + A[(i-1)*n + j];
                printf("%d ", A[i*n + j]);
            }

            A[i*n + i] = 1;
            printf("1\n");
        }

    }
    free(A);
    return 0;
}