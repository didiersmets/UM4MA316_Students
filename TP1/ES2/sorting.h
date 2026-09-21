#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(int* arr, int n){
    for(int j=0;j<n;j++){
        for(int i=0;i<n-j-1;i++){
            if(arr[i]>arr[i+1]){
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
            }
        }
    }
}

void insertionSort(int* arr, int n){
    for(int i=0;i<n-1;i++){
        if(arr[i]>arr[i+1]){
            for(int j=i+1;j>0;j--){
                if(arr[j]<arr[j-1]){
                    int tmp = arr[j];
                    arr[j] = arr[j-1];
                    arr[j-1] = tmp;
                }else{
                    break;
                }
            }
        }
    }
}

void merge(int* T, int p, int q, int r){
    int *S = malloc((r+1-p)*sizeof(int));

    for(int i=0;i<r-p;i++){
        if(T[p]<T[q+1]){
            S[i] = T[p];
            p++;
        }else{
            S[i] = T[q+1];
            q++;
        }
    }
    memcpy(T+p*sizeof(int),S,(r+1-p)*sizeof(int));
    free(S);
}

void mergeSort(int* arr, int p, int r){
    if(p<r){
        int q = (p+r)/2;
        mergeSort(arr, p, q);
        mergeSort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}