#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double rand_max = 100;

void insertionsort(int n){

    int tab[n];
    srand(time(NULL));
    for (int i=0; i < n; i++){
        tab[i] = (rand() % 100) + 1;
        printf("%d ", tab[i]);
    }

    printf("\n");

    int pos = 1;

    for (int i = 1; i < n; i++){
        for(int j = pos; j > 0; j--){
            if (tab[j] < tab[j-1]){
                int tmp = tab[j];
                tab[j] = tab[j-1];
                tab[j-1] = tmp;
            }
        }
        pos++;

    }

    for (int i=0; i < n; i++){
        printf("%d ", tab[i]);
    }
}

int main(int argc, char *argv[]) {
    insertionsort(atoi(argv[1]));
    printf("\n");
    return 1;

}