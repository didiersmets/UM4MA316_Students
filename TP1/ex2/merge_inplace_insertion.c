#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define THRESHOLD 4


double rand_max = 100;

void insertionsort(int *T, int n){
    int pos = 1;
    for (int i = 1; i < n; i++){
        for(int j = pos; j > 0; j--){
            if (T[j] < T[j-1]){
                int tmp = T[j];
                T[j] = T[j-1];
                T[j-1] = tmp;
            }
        }
        pos++;

    }
}


void merge_subroutine(int *T,  int p, int q, int r){
    int i = q;
    int j = q + 1;

    if (p > q || q >= r) {
        return;
    }

    if (T[q] <= T[q + 1]) {
        return;
    }
    


    while (i >= p && j <= r && T[i] > T[j]) {
        i--;
        j++;
    }

    int blockA = i+1;
    int blockB = q+1;

    while (blockA <= q && blockB < j) {
        int tmp = T[blockA];
        T[blockA] = T[blockB];
        T[blockB] = tmp;
        blockA++;
        blockB++;
    }

    merge_subroutine(T, p, i, q);
    merge_subroutine(T, q + 1, j - 1, r);

}

void merge_sort(int* T, int p, int r){
    if(p < r){
        int size = r - p + 1;
        
        if (size <= THRESHOLD){
            insertionsort(&T[p], size);
            return;
        }

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