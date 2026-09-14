#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){

    int n = atoi(argv[1]);
    if(n<=0){
        printf("Error, n must be > 0\n");
        return 1;
    }

    int* mat = (int*)malloc(n * n * sizeof(int));
    if(mat == NULL){
        printf("Error allocating memory");
        return 1;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            if(j>0 && j<i){
                mat[i*n + j] = mat[(i-1)*n + j-1] + mat[(i-1)*n + j];
                printf("%d", mat[i*n + j]);
            }else{
                mat[i*n + j] = 1;
                printf("%d", mat[i*n + j]); 
            }
        }
        printf("\n");
    }

    free(mat);

    return 0;
}