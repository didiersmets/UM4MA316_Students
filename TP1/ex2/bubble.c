#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double rand_max = 100;

void bubblesort(int n){

    int tab[n];
    srand(time(NULL));
    for (int i=0; i < n; i++){
        tab[i] = (rand() % 100) + 1;
        printf("%d ", tab[i]);
    }

    printf("\n");

    int pos = 0;

    for (int i=0; i < n; i++){
        for(int j=0; j < n - 1 - pos; j++){
            if (tab[j+1] < tab[j]){
                int tmp = tab[j+1];
                tab[j+1] = tab[j];
                tab[j] = tmp;
            }
        }
        pos++;

    }

    for (int i=0; i < n; i++){
        printf("%d ", tab[i]);
    }

}

int main(int argc, char *argv[]) {
    bubblesort(atoi(argv[1]));
    printf("\n");
    return 1;

}