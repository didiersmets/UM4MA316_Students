#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define THRESHOLD 16


void bubblesort(int *tab, int n){

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

}

void insertionsort(int *tab,int n){

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
}

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

void merge2_subroutine(int *TI, int *TF, int p, int q, int r){
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

void merge2_sort_internal(int* F, int* I, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        merge2_sort_internal(I, F, p, q);
        merge2_sort_internal(I, F, q + 1, r);
        merge2_subroutine(F, I, p, q, r);
    }
}

void merge2_sort(int *T, int N){
    int* B = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        B[i] = T[i];
    }
    merge2_sort_internal(B, T, 0, N-1);
    free(B);
}

void merge_inplace_subroutine(int *T,  int p, int q, int r){
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

    merge_inplace_subroutine(T, p, i, q);
    merge_inplace_subroutine(T, q + 1, j - 1, r);

}

void merge_inplace_sort(int* T, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        merge_inplace_sort(T, p, q);
        merge_inplace_sort(T, q + 1, r);
        merge_inplace_subroutine(T, p, q, r);
    }
}

void merge_hybrid_subroutine(int *T,  int p, int q, int r){
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

    merge_hybrid_subroutine(T, p, i, q);
    merge_hybrid_subroutine(T, q + 1, j - 1, r);

}

void merge_hybrid_sort(int* T, int p, int r){
    if(p < r){

        int size = r - p + 1;
        if (size <= THRESHOLD){
            insertionsort(&T[p], size);
            return;
        }

        int q = (p+r)/2;
        merge_hybrid_sort(T, p, q);
        merge_hybrid_sort(T, q + 1, r);
        merge_hybrid_subroutine(T, p, q, r);
    }
}

int main(int argc, char * argv[]) {
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000, 5000, 10000};
    srand(time(NULL));
    FILE *file = fopen("times.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int s = 0; s < 9; s++) {
        int n = sizes[s];

        int *original = malloc(sizeof(int) * n);
        int *bubble_tab = malloc(sizeof(int) * n);
        int *insertion_tab = malloc(sizeof(int) * n);
        int *merge_tab = malloc(sizeof(int) * n);
        int *merge2_tab = malloc(sizeof(int) * n);
        int *merge_inplace_tab = malloc(sizeof(int) * n);
        int *merge_hybrid_tab = malloc(sizeof(int) * n);


        for (int i=0; i < n; i++){
            original[i] = (rand() % 100) + 1;
        }

        memcpy(bubble_tab, original, sizeof(int) * n);
        memcpy(insertion_tab, original, sizeof(int) * n);
        memcpy(merge_tab, original, sizeof(int) * n);
        memcpy(merge2_tab, original, sizeof(int) * n);
        memcpy(merge_inplace_tab, original, sizeof(int) * n);        
        memcpy(merge_hybrid_tab, original, sizeof(int) * n);

        clock_t start = clock();
        bubblesort(bubble_tab, n);
        clock_t end = clock();
        double bubble_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        insertionsort(insertion_tab, n);
        end = clock();
        double insertion_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort(merge_tab, 0, n - 1);
        end = clock();
        double merge_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        merge2_sort(merge2_tab, n);
        end = clock();
        double merge2_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        merge_inplace_sort(merge_inplace_tab, 0, n - 1);
        end = clock();
        double merge_inplace_time = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        merge_hybrid_sort(merge_hybrid_tab, 0, n - 1);
        end = clock();
        double merge_hybrid_time = (double)(end - start) / CLOCKS_PER_SEC;


        fprintf(file, "%d %f %f %f %f %f %f\n", n, bubble_time, insertion_time, merge_time, merge2_time, merge_inplace_time, merge_hybrid_time);

        free(original);
        free(bubble_tab);
        free(insertion_tab);
        free(merge_tab);
        free(merge2_tab);
        free(merge_inplace_tab);
        free(merge_hybrid_tab);

    }

    fclose(file);

    system("gnuplot sorting_plot.gp");

    return 0;
}