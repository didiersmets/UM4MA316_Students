#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pascal_triangle(int *A, size_t n) {
    int new_val = 0;
    int buffer_val = 0;
    printf("1\n");
    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i+1; j++) {
            if (j==i) {
                printf("%d\n", A[j]);
                A[j-1] = (j>1)?buffer_val:1;
            }
            else if (j==0) {
                printf("%d, ", A[j]);
            }
            else {
                new_val = A[j-1] + A[j];
                printf("%d, ", new_val);
                A[j-1] = (j>1)?buffer_val:1;
                buffer_val = new_val;
            }
        }
    }

}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "%s <integer>", argv[0]);
        return 1;
    }

    long n;
    char *endptr;
    n = strtol(argv[1], &endptr, 10);
    int A[n];
    for (long i = 0; i < n; i++) {
            A[i] = 1;
        }

    pascal_triangle(A, n);

    return 0;
}
