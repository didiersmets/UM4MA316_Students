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

    while((array[i + 1] < array[i]) && i < n) {
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

void merge(int *T, int p, int q, int r) {
    int *S = malloc((r - p + 1) * sizeof(int));

    memcpy(S, T, (r + 1) * sizeof(int));

    int p1 = p;
    int p2 = q + 1;

    for(int i = 0; i < r + 1; i++) {
        if(T[p1] < T[p2]) {
            S[i] = T[p1];
            p1++;
        }
        else {
            S[i] = T[p2];
            p2++;
        }
    }

    memcpy(T, S + p * sizeof(int), (r - p + 1) * sizeof(int));
    free(S);
}

void mergeSort(int *T, int p, int r) {
    if(p<r) {
        int q = (p + r) / 2;
        mergeSort(T, p, q);
        mergeSort(T, q + 1, r);
        merge(T, p, q, r);
    }
}
 