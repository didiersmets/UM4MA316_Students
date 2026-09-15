#include <stdlib.h>
#include <stdio.h>

int main (int argc, char ** argv)
{
    int n = atoi(argv[1]);

    int*A = malloc(n*n*sizeof(int));

    for (int i= 0; i<n ; i++) {
        for (int j=0 ; j<=i ; j++) {
            if (j>0 && j<i){
                A[i * n + j] = A[(i-1) * n + (j-1)] + A[(i-1) * n + j];
            } else {
                A[i * n + j] = 1;
            }
            printf("%d ", A[i * n + j]);
        }
    printf("\n");
    }
    
    free(A);
    return 0;

}

