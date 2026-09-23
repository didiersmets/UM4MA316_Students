#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "print-array.h"
#include "merge-sort.h"


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

    print_int_array(A, n, 1);

    int T[n];

    memcpy(T, A, n * sizeof(int));
    printf("A copied to T.\n");
    print_int_array(T, n, 1);

    merge_sort(A, 0, n, T);

    print_int_array(A, n, 1);

    return 0;
}
