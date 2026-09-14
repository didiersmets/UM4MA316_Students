#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int n = atoi(argv[1]);
	int*A = malloc(n*sizeof(int));
	A[0] = 1;
	{
		for(int i=0; i<n; i++){
			
			A[i] = 1;
			for(int j=0; j<=i; j++){

				printf("%d ", A[j]);
			}
			printf("\n");
			for(int k=i; k>0; k--){
				A[k] = A[k] + A[k-1];
			}
		}
	}
	free(A);
	return 0;
}



