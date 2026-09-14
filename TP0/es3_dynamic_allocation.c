#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("no integer provided in the command line\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if(n <= 0) {
        printf("insert a positive integer\n");
        return 1;
    }

    int *pascal_mat = malloc(n * n * sizeof(int));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            if(0 < j && j < i) {
                pascal_mat[i * n + j] = pascal_mat[(i - 1) * n + j - 1] + pascal_mat[(i - 1) * n + j];
                printf("%d ", pascal_mat[i * n + j]);
            }
            else {
                pascal_mat[i * n + j] = 1;
                printf("%d ", pascal_mat[i * n + j]);
            }
        }
        printf("\n");
    }

    free(pascal_mat);


    return 0;
}