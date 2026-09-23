#include <stdio.h>
#include "print-array.h"


void print_int_array(int* A, size_t cols, size_t rows) {

    for (size_t i = 0; i < rows; i++) {
	for(size_t j = 0; j < cols; j++) {
	    printf("%d\t", A[i * cols + j]);
	}
	puts("");
    }
}
