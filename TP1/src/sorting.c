#include <stddef.h>
#include <stdio.h>


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

/*
void insertion_sort(int *A, size_t size) {
    
}

void merge_sort(int *A, size_t size) {
    
}
*/

void print_array(int* A, size_t size) {
    for (size_t i = 0 ; i < size ; i++) {
        printf("%d\t", A[i]);
    }
    puts("");
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
    bubble_sort(A, n);
    print_array(A, n);

    return 0;
}