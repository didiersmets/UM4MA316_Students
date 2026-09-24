#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    int idx1 = p;
    int mid = q;
    int idx2 = q+1;

    for(int i=0;i<=r-p;i++){
        if(idx2>r || (idx1<=mid && T[idx1]<=T[idx2])){
            S[i] = T[idx1++];
        }else{
            S[i] = T[idx2++];
        }
    }
    memcpy(&T[p],S,(r+1-p)*sizeof(int));
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


//MergeSort faster
void mergeR(int* unsorted, int p, int q, int r, int* sorted){
    int idx1 = p;
    int mid = q;
    int idx2 = q+1;

    for(int i=0;i<=r-p;i++){
        if(idx2>r || (idx1<=mid && unsorted[idx1]<=unsorted[idx2])){
            sorted[i+p] = unsorted[idx1++];
        }else{
            sorted[i+p] = unsorted[idx2++];
        }
    }
}

void mergeSortRecursive(int* unsorted, int p, int r, int* sorted){
    if(p<r){
        int q = (p+r)/2;
        mergeSortRecursive(sorted,p,q,unsorted);
        mergeSortRecursive(sorted,q+1,r,unsorted);
        mergeR(unsorted,p,q,r,sorted);
    }else if(p==r){
        sorted[p] = unsorted[p];
    }
}

void mergeSortUser(int *A, int n){
    int* B = malloc(n*sizeof(int));
    memcpy(B,A,n*sizeof(int));
    mergeSortRecursive(B,0,n-1,A);
    free(B);
}