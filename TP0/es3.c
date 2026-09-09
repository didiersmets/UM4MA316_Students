#include <stdio.h>

int main(){

    int n;

    printf("Insert input: \n");
    scanf("%d", &n);

    int mat[n][n];

    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            if(j>0 && j<i){
                mat[i][j] = mat[i-1][j-1] + mat[i-1][j];
                printf("%d", mat[i][j]);
            }else{
                mat[i][j] = 1;
                printf("%d", mat[i][j]); 
            }
        }
        printf("\n");
    }

    return 0;
}