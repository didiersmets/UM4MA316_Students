#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"
#include <time.h>
#include "mergeSortThread.h"

#define N_ALGORITHMS 5
#define QUADRATIC_MAX 100000

static double now(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

int main(int argc, char* argv[]){
    int N[] = {10, 20, 50, 100, 200, 500, 1000, 10000, 100000, 1000000};
    int n_sizes = sizeof(N)/sizeof(N[0]);

    const char* names[N_ALGORITHMS] = {
        "Bubble Sort",
        "Insertion Sort",
        "Merge Sort",
        "Merge Sort Ping Pong",
        "Merge Sort Threads"
    };

    srand(time(NULL));

    FILE *fptr;
    fptr = fopen("Time_rep.txt", "w");

    for(int i=0;i<n_sizes;i++){
        fprintf(fptr, "\n\n\nArray size: %d\n", N[i]);
        int *base_arr = malloc(N[i]*sizeof(int));
        int *arr = malloc(N[i]*sizeof(int));

        for(int k=0;k<N[i];k++){
            int val = rand();
            base_arr[k] = val;
        }

        for(int j=0;j<N_ALGORITHMS;j++){

            fprintf(fptr, "\n\n%s\n", names[j]);

            if(j<2 && N[i]>QUADRATIC_MAX){
                fprintf(fptr, "Skipped (O(n^2), too slow)\n");
                continue;
            }

            memcpy(arr, base_arr, N[i]*sizeof(int));

            /*
            for(int k=0;k<N[i];k++){
                printf("%d ", arr[k]);
            }
            printf("\n\n");
            */

            double start = now();
            if(j==0){
                bubbleSort(arr,N[i]);
            }else if(j==1){
                insertionSort(arr,N[i]);
            }else if(j==2){
                mergeSort(arr,0,N[i]-1);
            }else if(j==3){
                mergeSortUser(arr,N[i]);
            }else{
                mergeSortParallelUser(arr,N[i]);
            }

            double end = now();
            double time = end-start;
            fprintf(fptr, "Execution time: %2f\n", time);

            /*
            for(int k=0;k<N[i];k++){
                printf("%d ", arr[k]);
            }
            printf("\n\n\n");
            */
        }

        free(base_arr);
        free(arr);
    }

    /*
    int arr[]  = {11,54,23,6,7,89,4,2,8,45};

    for(int k=0;k<10;k++){
        printf("%d ", arr[k]);
    }
    printf("\n\n");

    //bubbleSort(arr, 10);
    //insertionSort(arr,10);
    //mergeSort(arr, 0, 9);
    //mergeSortUser(arr,10);
    mergeSortParallelUser(arr,10);

    for(int k=0;k<10;k++){
        printf("%d ", arr[k]);
    }
    */

    fclose(fptr);
    return 0;
}
