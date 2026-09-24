#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"
#include <time.h>

int main(int argc, char* argv[]){
    /*
    int N[] = {10, 20, 50, 100, 200, 500, 1000};

    srand(time(NULL));

    FILE *fptr;
    fptr = fopen("Time_rep.txt", "w");

    for(int i=0;i<7;i++){
        fprintf(fptr, "\n\n\nArray size: %d\n", N[i]);
        int *base_arr = malloc(N[i]*sizeof(int));
        int *arr = malloc(N[i]*sizeof(int));

        for(int k=0;k<N[i];k++){
            int val = rand() % 2000;
            base_arr[k] = val;
        }

        for(int j=0;j<3;j++){

            if(j==0){
                fprintf(fptr, "\n\nBubble Sort\n");
            }else if(j==1){
                fprintf(fptr, "\n\nInsertion Sort\n");
            }else{
                fprintf(fptr, "\n\nMerge Sort\n");
            }

            memcpy(arr, base_arr, N[i]*sizeof(int));

            /*
            for(int k=0;k<N[i];k++){
                printf("%d ", arr[k]);
            }
            printf("\n\n");
            *

            clock_t start = clock();
            if(j==0){
                bubbleSort(arr,N[i]);
            }else if(j==1){
                insertionSort(arr,N[i]);
            }else{
                mergeSort(arr,0,N[i]-1);
            }

            clock_t end = clock();
            double time = (double)(end-start)/CLOCKS_PER_SEC;
            fprintf(fptr, "Execution time: %2f\n", time);

            /*
            for(int k=0;k<N[i];k++){
                printf("%d ", arr[k]);
            }
            printf("\n\n\n");
            *
        }

        free(base_arr);
        free(arr);
    }
    */

    
    int arr[]  = {11,54,23,6,7,89,4,2,8,45};

    for(int k=0;k<10;k++){
        printf("%d ", arr[k]);
    }
    printf("\n\n");

    //bubbleSort(arr, 10);
    //insertionSort(arr,10);
    //mergeSort(arr, 0, 9);
    mergeSortUser(arr,10);

    for(int k=0;k<10;k++){
        printf("%d ", arr[k]);
    }
    

    //fclose(fptr);
    return 0;
}