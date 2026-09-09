#include <stdio.h>
#include <stdlib.h>


void pascaltriangle(int n){
    
    int tab[n*n];
    tab[0]=1;
    printf("%d   \n", 1);

    for (int i=1; i < n; i++){
        for (int j=0; j <= i; j++){
            if (j == 0 || j == i ){
                tab[i*n + j]=1;
            } else {
            tab[i*n + j] = tab[(i-1)*n + j-1] + tab[(i-1)*n + j];
            }
            printf("%d   ", tab[i*n + j]);
        }
        printf("\n");
    }


}

int main(int argc, char *argv[]){
    pascaltriangle(atoi(argv[1]));
    return 0;
}