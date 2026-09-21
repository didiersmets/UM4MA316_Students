#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double rand_max = 100;

void merge_subroutine(int *TI, int *TF, int p, int q, int r){
    int i = p;
    int j = q + 1;
    int k = p;

    while (i <= q && j <= r) {
        if (TI[i] < TI[j]) {
            TF[k] = TI[i];
            i++;
        }
        else {
            TF[k] = TI[j];
            j++;
        }
        k++;
    }

    while (i <= q) {
        TF[k] = TI[i];
        i++;
        k++;
    }

    while (j <= r) {
        TF[k] = TI[j];
        j++;
        k++;
    }


}

void merge_sort_internal(int* F, int* I, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        merge_sort_internal(I, F, p, q);
        merge_sort_internal(I, F, q + 1, r);
        merge_subroutine(F, I, p, q, r);
    }
}

void merge_sort(int *T, int N){
    int* B = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        B[i] = T[i];
    }
    merge_sort_internal(B, T, 0, N-1);
    free(B);
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

    merge_sort(T, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");
    free(T);
    return 0;
}