#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void print_array(int* A, size_t size) {
    for (size_t i = 0 ; i < size ; i++) {
        printf("%d\t", A[i]);
    }
    puts("");
}

void bubble_sort(int *A, size_t size) {
    int buff = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (A[j] > A[j+1]) {
                buff = A[j];
                A[j] = A[j+1];
                A[j+1] = buff;
            }
        }
    }
}


void insertion_sort(int *A, size_t size) {
    int buff = 0;
    int previous = 0;
    int j = 0;
    for (size_t i = 1; i < size; i++) {
        buff = A[i];
        previous = A[i-1];
        j = i;
        while (buff < previous && j!=0) {
            

            A[j-1] = buff;
            A[j] = previous;

            j -= 1;
            
            buff = A[j];
            previous = A[j-1];
        }
    }
}

void Merge(int *A, size_t p, size_t q, size_t r) {
    puts("Entering merge. Section to sort: ");
    print_array(&A[p],r-p);
    int *T = malloc(r-p);
    int index1 = p;
    int index2 = q;
    int val1 = A[p]; 
    int val2 = A[q];
    for (size_t i = 0 ; i < r - p ; i++) {
        val1 = A[index1]; 
        val2 = A[index2];
        T[i] = (val1 < val2) ? val1 : val2;
        index1 = (val1 < val2) ? index1 + 1 : index1;
        index2 = (val1 < val2) ? index2 : index2 + 1;
    }
    memcpy(&A[p], T, (r-p) * sizeof(int));
    print_array(T,r-p);
    free(T);
}

void MergeSort(int *A, size_t p, size_t r) {
    int q = 0;
    if (p < r) {
        puts("Entering if in merge sort.");
        q = floor((p+r)/2);
        printf("p is %ld and q is %d\n", p, q);
        MergeSort(A, p, q);
        MergeSort(A, q+1, r);
        Merge(A, p, q, r);
    }
}



int main(void) {

    size_t n = 10;
    
    int A[n];
    A[0] = 11;
    A[1] = 8;
    A[2] = 54;
    A[3] = 23;
    A[4] = 6;
    A[5] = 7;
    A[6] = 89;
    A[7] = 4;
    A[8] = 2;
    A[9] = 45;

    print_array(A, n);
    MergeSort(A, 0, n);
    print_array(A, n);

    return 0;
}