#include "../include/sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]) {

    srand(time(NULL));

    int N[7] = {10, 20, 50, 100, 200, 500, 1000};

    for(int i = 0; i < sizeof(N) / sizeof(int); i++) {

        printf("\n\
------------------------------------------------\n\
sorting array of length %d\n\
------------------------------------------------\n", N[i]);

        int *arr = malloc(N[i] * sizeof(int));
        int *arr1 = malloc(N[i] * sizeof(int));
        int *arr2 = malloc(N[i] * sizeof(int));

        for(int j = 0; j < N[i]; j++) {
            arr[j] = rand() % 100;
        }

        memcpy(arr1, arr, N[i] * sizeof(int));
        memcpy(arr2, arr, N[i] * sizeof(int));

        printf("array:\n");
        for(int j = 0; j < N[i]; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");

        // bubble sort

        bubbleSort(arr, N[i]);

        // insertion sort

        insertionSort(arr1, N[i]);

        // merge sort

        mergeSort(arr2, 0, N[i] - 1);

        // sorted array and check that the sorting is the same using all three algorithms

        for(int j = 0; j < N[i]; j++) {
            if(arr[j] != arr1[j] || arr1[j] != arr2[j]) {
                printf("different sorting resulted from the algorithms\n");
                return 1;
            }
        }

        printf("sorted array:\n");
        for(int j = 0; j < N[i]; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
        
    }

    return 0;
}