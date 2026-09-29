#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void bubble_sort(int *T, int N){
	for(int i=N-1; i>0; --i){
		for(int j=0; j<i; ++j){
			if(T[j]>T[j+1]){
				int tmp=T[j];
				T[j]=T[j+1];
				T[j+1]=tmp;
			}
		}
	}
}

void insertion_sort(int *T, int N){
	for(int i=1; i<N; ++i){
		int j=i;
		while(j>0&&T[j]<=T[j-1]){
			int tmp=T[j];
			T[j]=T[j-1];
			T[j-1]=tmp;
			--j;
		}
	}
}

void merge(int *T, int p, int q, int r){
	int *S=malloc((r-p+1)*sizeof(int));
	int k=0;
	int i=p;
	int j=q+1;
	while(k<r-p+1){
		if(i<=q&&T[i]<=T[j]){
			S[k]=T[i];
			++i;
			++k;
		}else if(j<=r&&T[j]<=T[i]){
			S[k]=T[j];
			++j;
			++k;
		}else{
			while(i<=q){
				S[k++]=T[i++];
			}
			while(j<=r){
				S[k++]=T[j++];
			}
		}
	}
	for(int i=0; i<k; ++i){
		T[p+i]=S[i];
	}
	free(S);
}

void mergesort(int *T, int p, int r){
	if(p<r){
		int q=(p+r)/2;
		mergesort(T, p, q);
		mergesort(T, q+1, r);
		merge(T, p, q, r);
	}
}

void merge_sort(int *T, int N){
	mergesort(T, 0, N-1);
}


int main(void){
	int size[]={10, 20, 50, 100, 200, 500, 1000};
	int s=sizeof(size)/sizeof(int);
	FILE *fb=fopen("bubble_sorting.dat", "w");
	FILE *fi=fopen("insertion_sorting.dat", "w");
	FILE *fm=fopen("merge_sorting.dat", "w");
	
	clock_t t;
	double time_taken;

	for(int i=0; i<s; ++i){
		int N=size[i];
		int *A=malloc(N*sizeof(int));
		int *B=malloc(N*sizeof(int));
		int *C=malloc(N*sizeof(int));
		for(int j=0; j<N; ++j){
			int x=rand();
			A[j]=x;
			B[j]=x;
			C[j]=x;
		}
		
		t=clock();
		bubble_sort(A,N);
		t=clock()-t;
		time_taken=((double)t)/CLOCKS_PER_SEC;
		fprintf(fb, "%d %.10f\n", N, time_taken);

                t=clock();
                insertion_sort(B,N);
                t=clock()-t;
                time_taken=((double)t)/CLOCKS_PER_SEC;
                fprintf(fi, "%d %.10f\n", N, time_taken);

                t=clock();
                merge_sort(C,N);
                t=clock()-t;
                time_taken=((double)t)/CLOCKS_PER_SEC;
                fprintf(fm, "%d %.10f\n", N, time_taken);
	}
	fclose(fb);
	fclose(fi);
	fclose(fm);

	system("gnuplot sorting.gp");
}



