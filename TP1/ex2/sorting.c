#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main(int argc, char * argv[]) {
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000, 5000, 10000, 20000, 50000, 100000};
    srand(time(NULL));
    FILE *file = fopen("times.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int s = 0; s < 12; s++) {
        int n = sizes[s];

        int *original = malloc(sizeof(int) * n);
        int *bubble_tab = malloc(sizeof(int) * n);
        int *insertion_tab = malloc(sizeof(int) * n);
        int *merge_tab = malloc(sizeof(int) * n);

        for (int i=0; i < n; i++){
            original[i] = (rand() % 100) + 1;
        }

        memcpy(bubble_tab, original, sizeof(int) * n);
        memcpy(insertion_tab, original, sizeof(int) * n);
        memcpy(merge_tab, original, sizeof(int) * n);

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

        fprintf(file, "%d %f %f %f\n", n, bubble_time, insertion_time, merge_time);

        free(original);
        free(bubble_tab);
        free(insertion_tab);
        free(merge_tab);
    }

    fclose(file);

    system("gnuplot sorting_plot.gp");

    return 0;
}