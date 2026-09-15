#include <stdio.h>

void insertion_sort(int *A, int n){
	int i = 0;
	
	
	while (i < n && A[i] <= A[i+1]){
		i++;
	}

	

	for(i; i<n-1; i++){
		int j = i;
		while (A[j+1] < A[j]){
                        int temp = A[j];
                       	A[j] = A[j+1];
                       	A[j+1] = temp;
                       	if (j > 0){
                               	j = j - 1;
                      	}
			else{break;}
               	}
	}
}
            



	
	


int main(){
	
	int tab[] = {6,11,23,54,7,89,4,2,8,45};
        insertion_sort(tab,10);
	int i;	
	for(i = 0;i < 10;i++){
		printf("%d ",tab[i]);
	}
	printf("\n");
	return 0;
}
