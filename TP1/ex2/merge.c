#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double rand_max = 100;

void merge_subroutine(int *T,  int p, int q, int r){
    int *tab = malloc(sizeof(int)*(r-p+1));
    int i = p;
    int j = q + 1;
    int k = 0;

    while (i <= q && j <= r) {
        if (T[i] < T[j]) {
            tab[k] = T[i];
            i++;
        }
        else {
            tab[k] = T[j];
            j++;
        }
        k++;
    }

    while (i <= q) {
        tab[k] = T[i];
        i++;
        k++;
    }

    while (j <= r) {
        tab[k] = T[j];
        j++;
        k++;
    }

    for (int x = 0; x < r - p + 1; x++) {
        T[p + x] = tab[x];
    }

    free(tab);
}

void merge_sort(int* T, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        merge_sort(T, p, q);
        merge_sort(T, q + 1, r);
        merge_subroutine(T, p, q, r);
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int *T = malloc(sizeof(int) * n);
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        T[i] = (rand() % 100) + 1;
        printf("%d ", T[i]);
    }
    printf("\n");

    merge_sort(T, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");
    free(T);
    return 0;
}