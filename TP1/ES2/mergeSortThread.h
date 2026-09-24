#ifndef MERGESORTTHREAD_H
#define MERGESORTTHREAD_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

#define THREAD_THRESHOLD 1000

struct ThreadArgs{
    int* arr;
    int p;
    int r;
};

//parallelized merge sort (merge and mergeSort come from sorting.h)
void* mergeSortPar(void* arg){
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    int p = args->p;
    int r = args->r;
    int* arr = args->arr;

    if(p<r){
        if((r-p)<THREAD_THRESHOLD){
            mergeSort(arr,p,r);
            return NULL;
        }

        int q = (p+r)/2;

        struct ThreadArgs left_args = {arr,p,q};
        pthread_t left_thread;
        pthread_create(&left_thread,NULL,mergeSortPar,&left_args);

        struct ThreadArgs right_args = {arr,q+1,r};
        mergeSortPar(&right_args);

        pthread_join(left_thread,NULL);

        merge(arr,p,q,r);
    }

    return NULL;
}

void mergeSortParallelUser(int* arr, int n) {
    struct ThreadArgs args = {arr, 0, n - 1};
    mergeSortPar(&args);
}

#endif
