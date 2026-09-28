#include <stdlib.h>
void bubble_sort(int *T, int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (T[j] > T[j + 1]) {
                int tmp = T[j];
                T[j] = T[j + 1];
                T[j + 1] = tmp;
            }
}
void insertion_sort(int *T, int n) {
    for (int k = 1; k < n; ++k) {
        int key = T[k];
        int j = k - 1;
        while (j >= 0 && T[j] > key) {
            T[j + 1] = T[j];
            --j;
        }
        T[j + 1] = key;
    }
}
static void merge(int *T, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; ++i) L[i] = T[p + i];
    for (int j = 0; j < n2; ++j) R[j] = T[q + 1 + j];
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) T[k++] = L[i++];
        else              T[k++] = R[j++];
    }
    while (i < n1) T[k++] = L[i++];
    while (j < n2) T[k++] = R[j++];
    free(L);
    free(R);
    // l'idée est de compier le n1 et n2 respectivement les partie a gauche et a droite avant de les trier et ensuite les replacer dans T
}
static void merge_sort_rec(int *T, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort_rec(T, p, q);
        merge_sort_rec(T, q + 1, r);
        merge(T, p, q, r);
        // trie a gauche et a droite avant le merge pour regrouper
    }
}
void merge_sort(int *T, int n) {
    merge_sort_rec(T, 0, n - 1);
    // on effectue juste pour le tableau entier avant decoupage
    //juste une recurence sur le tableau
}

