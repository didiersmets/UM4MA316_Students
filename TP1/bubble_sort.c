void bubble_sort(int *A, int n){
	int m=n;
	while(m>1){
		for(i=0, i<m-1, i++){
			if(A[i]<A[i+1]){
				int tmp=A[i];
				A[i]=A[i+1];
				A[i+1]=tmp;
			}
		}
		m--;
	}
}

void insertion_sort(int *A, int n){
	if(n>=2){
		for(i=1, i<n, i++){
			int j=i;
			while(j>0 && A[j]<=A[j-1]){
				int tmp=A[j];
				A[j]=A[j-1];
				A[j-1]=tmp;
				j--;
			}
		}
	}
}

void merge_sort(int *A, int p, int q, int r){
	int i=p

