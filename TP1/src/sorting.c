#include "../include/circular_buffer_queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int *array, int n) {

    int tmp = 0;
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < n - j - 1; i++) {
            if(array[i] > array[i+1]) {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
            }
        }
    }
}

void insertionSort(int *array, int n) {

    int tmp = 0;
    int k = 1;
    int i = 0;

    while(i < n-1 && array[i] < array[i + 1]) {
        k++;
        i++;
    }

    for(i = k; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(array[j] < array[j-1]) {
                tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
            else break;
        }
    }
}

void merge(int *T, int p, int q, int r, int *S) {

    int p1 = p;
    int p2 = q + 1;

    for(int i = p; i < r + 1; i++) {
        if(p2 == r + 1 || (p1 != q + 1 && T[p1] <= T[p2])) {
            S[i] = T[p1++];
        }
        else {
            S[i] = T[p2++];
        }
    }

    memcpy(T + p, S + p, (r - p + 1) * sizeof(int));
}

void mergeSortRecursive(int *T, int p, int r, int *S) {
    if(p<r) {
        int q = (p + r) / 2;
        mergeSortRecursive(T, p, q, S);
        mergeSortRecursive(T, q + 1, r, S);
        merge(T, p, q, r, S);
    }
}

void mergeSort(int *T, int n) {
    int *S = malloc(n * sizeof(int));
    // memcpy(S, T, n * sizeof(int));
    mergeSortRecursive(T, 0, n-1, S);
    // memcpy(T, S, n*sizeof(int));
    free(S);
}
 