#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	if (argc!=2){
		printf("Please enter the C filename and the line number.");
		return 1;
	}
	int n = atoi(argv[1]);
	if (n<=0){
		printf("Please re-enter.");
		return 1;
	}
	int *A = malloc(n*sizeof(int));
	for(int i=0; i<n; i++){
		for(int j=i; j>=0; j--){
			if(j==0||j==i){
				A[j]=1;
			}else{
				A[j]=A[j]+A[j-1];
			}}
		for(int k=0; k<=i; k++){
			printf("%2d ", A[k]);
		}
		printf("\n");
	}
	free(A);
	return 0;
}
