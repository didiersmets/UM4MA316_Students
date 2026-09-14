#include<stdio.h>
#include<stdlib.h>


int main (int argc, char **argv){

	int n = atoi(argv[1]);
	int *mat  = malloc(n * n * sizeof(int));

	for (int i=0;i<n;i++){
		mat[i*n]=1;
		for (int j=1;j<i;j++){
				mat[i*n+j] = mat[(i-1)*n + j-1] + mat[(i-1)*n + j];
		}
		mat[i*(n+1)]=1;
	}

	for (int i=0; i<n; i++){
		for (int j=0; j<=i; j++){
			printf("%d ", mat[i*n+j]);
		}
		printf("\n");
	}

	free(mat);
	return 0;
}

