#include "../include/sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]) {

    srand(time(NULL));

    int N[1] = {5};

    for(int i = 0; i < sizeof(N) / sizeof(int); i++) {

        int *arr = malloc(N[i] * sizeof(int));
        int *arr1 = malloc(N[i] * sizeof(int));
        int *arr2 = malloc(N[i] * sizeof(int));

        for(int j = 0; j < N[i]; j++) {
            arr[j] = rand();
        }

        memcpy(arr1, arr, N[i] * sizeof(int));
        memcpy(arr2, arr, N[i] * sizeof(int));

        printf("array:\n");
        for(int j = 0; j < N[i]; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        // bubble sort

        for(int j = 0; j < N[i]; j++) {
            bubbleSort(arr, N[i]);
        }

        printf("sorted array using bubble sort:\n");

        for(int j = 0; j < N[i]; j++) {
            printf("%d ", arr[j]);
        }

        printf("\n");

        // insertion sort

        printf("sorted array using insertion sort:\n");

        for(int j = 0; j < N[i]; j++) {
            insertionSort(arr1, N[i]);
        }

        for(int j = 0; j < N[i]; j++) {
            printf("%d ", arr1[j]);
        }

        printf("\n");

        // merge sort

        printf("sorted array using merge sort:\n");

        for(int j = 0; j < N[i]; j++) {
            mergeSort(arr2, 0, N[i] - 1);
        }

        for(int j = 0; j < N[i]; j++) {
            printf("%d ", arr2[j]);
        }

        printf("\n");

        
    }

    return 0;
}