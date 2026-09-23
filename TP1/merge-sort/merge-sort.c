#include <stddef.h>
#include "merge-sort.h"
#include "print-array.h"


void merge(const int *A, int *T, size_t start, size_t p, size_t size) {
    size_t j = start;
    size_t k = start + p;

    for (size_t i = start; i < start + size; i++) {
	if (k >= start + size || (j < start + p && A[j] <= A[k])) {
	    T[i] = A[j];
	    j++;
	}
	else {
	    T[i] = A[k];
	    k++;
	}
    }
    print_int_array(T + start, size, 1);
}

void merge_sort(int *A, size_t start, size_t size, int *T) {
    
    if (size == 1) {
	print_int_array(A+start, size, 1);
	return;
    }

    size_t p = size/2;
    
    merge_sort(T, start, p, A);
    merge_sort(T, start + p, size - p, A);
    merge(T, A, start, p, size);
}
