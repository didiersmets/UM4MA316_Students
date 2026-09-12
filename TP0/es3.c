#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
	printf("no integer n provided in the command line\n");
	return 0;
    }

    int n = atoi(argv[1]);

    int pascal_mat[n][n];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            if(0 < j && j < i) {
                pascal_mat[i][j] = pascal_mat[i-1][j-1] + pascal_mat[i-1][j];
                printf("%d ", pascal_mat[i][j]);
            }
            else {
                pascal_mat[i][j] = 1;
                printf("%d ", pascal_mat[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
