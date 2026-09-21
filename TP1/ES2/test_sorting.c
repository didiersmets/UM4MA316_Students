#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int main(int argc, char* argv[]){

    /*
   int N[] = {10, 20, 50, 100, 200, 500, 1000};

    for(int i=0;i<7;i++){
        int *arr = malloc(N[i]*sizeof(int));

        for(int j=0;j<N[i];j++){
            int val = rand();
            arr[j] = val;
        }
        
        bubbleSort(arr,N[i]);

        for(int k=0;k<N[i];k++){
            printf("%d ", arr[k]);
        }

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
    mergeSort(arr, 0, 10-1);

    for(int k=0;k<10;k++){
        printf("%d ", arr[k]);
    }
    

    return 0;
}