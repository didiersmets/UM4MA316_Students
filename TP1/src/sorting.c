#include <stdio.h>
#include <stdbool.h>
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
        for(j=i; j>0; j--){
           while(array[j] < array[j-1]){
                tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
        }
    }
}

void merge(int *T, int p, int q, int r) {
    int n = r - p + 1;
    int temp[n];

    int i = p;      
    int j = q + 1;   
    int k = 0;      

    while (i <= q && j <= r) {
        if (T[i] <= T[j]) {
            temp[k] = T[i];
            i++;
        } else {
            temp[k] = T[j];
            j++;
        }
        k++;
    }

    while (i <= q) {
        temp[k] = T[i];
        i++;
        k++;
    }

    while (j <= r) {
        temp[k] = T[j];
        j++;
        k++;
    }

    for (int x = 0; x < n; x++) {
        T[p + x] = temp[x];
    }
}

void mergSort(int* array, int p, int r){
    if(p<r){
        int q;
        q = (p+r)/2;
        mergSort(array,p,q);
        mergSort(array,q+1,r);
        merge(array,p,q,r);
    }
}