#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sorting.h"

void bubbleSort(int* array, int n){
    int tmp, k;
    k=n;
    while(k>1){
        bool swapped = false;
        for(int i=0; i<k-1;i++){
            if(array[i] > array[i+1]){
                tmp = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp;
                swapped = true;
            }
        }
        if(!swapped) 
            break;
        k--;
    }

}

void insertionSort(int* array, int n){
    int i,j, tmp;
    for(i=1; i<n; i++){
        j=i;
        while(j>0 && array[j] < array[j-1]){
            tmp = array[j];
            array[j] = array[j-1];
            array[j-1] = tmp;
            j--;
        }
    }
}

void merge(int *T, int p, int q, int r) {
    int n = r - p + 1;
    int *S = malloc(n*sizeof(int));

    int i = p;      
    int j = q + 1;   
    int k = 0;      

    while (i <= q && j <= r) {
        if (T[i] <= T[j]) {
            S[k] = T[i];
            i++;
        } else {
            S[k] = T[j];
            j++;
        }
        k++;
    }

    while (i <= q) {
        S[k] = T[i];
        i++;
        k++;
    }

    while (j <= r) {
        S[k] = T[j];
        j++;
        k++;
    }

    for (int x = 0; x < n; x++) {
        T[p + x] = S[x];
    }

    free(S);
}

void mergeSortRecursive(int* array, int p, int r){
    if(p<r){
        int q;
        q = (p+r)/2;
        mergeSortRecursive(array,p,q);
        mergeSortRecursive(array,q+1,r);
        merge(array,p,q,r);
    }
}

void mergeSort(int* array, int n){
    mergeSortRecursive(array, 0, n-1);
}

static void mergePingPong(int *A, int *B, int p, int q, int r){
    int i = p;      
    int j = q + 1;   
    int k = p;      

    while (i <= q && j <= r) {
        if (A[i] <= A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    while (i <= q) {
        B[k] = A[i];
        i++;
        k++;
    }

    while (j <= r) {
        B[k] = A[j];
        j++;
        k++;
    }
}


static void mergeSortPingPong(int *unsorted, int *sorted, int p, int r){
    if(p<r){
        int q;
        q = (p+r)/2;
        mergeSortPingPong(sorted, unsorted, p, q);
        mergeSortPingPong(sorted, unsorted, q+1, r);
        mergePingPong(unsorted, sorted, p,q,r);
    }
}

void userPingPong(int *A, int n){
    int *B = malloc(n*sizeof(int));
    memcpy(B,A,n*sizeof(int));
    mergeSortPingPong(B,A,0,n-1);
    free(B);
}