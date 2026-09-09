#include <stdio.h>
#include <stdlib.h>


void pascaltriangle(int n){
    
    int tab[n];
    tab[0]=1;
    printf("%d   \n", 1);

    for (int i=1; i < n; i++){
        for (int j = i; j >= 0; j--){
            if (j == 0 || j == i ){
                tab[j]=1;
            } else {
            tab[j] = tab[j]+tab[j-1];
            }
        }
        for (int j = 0; j < i+1 ; j++){
            printf("%d   ", tab[j]);

        }
        printf("\n");
    }


}

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("need an int in argv[i] \n");
        return 1;
    }
    pascaltriangle(atoi(argv[1]));
    return 0;
}