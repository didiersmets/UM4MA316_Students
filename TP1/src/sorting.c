#include <stdlib.h> 
#include "sorting.h"
#include <string.h>


bool is_sorted(const int *T, int N) {
	for (int i = 0; i + 1 < N; ++i) {
		if (T[i] > T[i + 1]) {
			return false;
		}
	}
	return true;
}


void merge(const int *A, int sA, const int *B, int sB, int *C) {
	int idxA = 0;
	int idxB = 0;
	for (int idxC = 0; idxC < sA + sB; idxC++) {
		if ( idxB >= sB || (idxA < sA && A[idxA] <= B[idxB])) {
		C[idxC] = A[idxA++];
		}
		else {
			C[idxC] = B[idxB++];
		}
	}
}

void merge_sort_recursive(int *T, int p, int r) {

	if (r<=p) {
		return;
	}

	int *TT = malloc((r-p+1) * sizeof(int));
	memcpy(TT, &T[p], (r-p+1) * sizeof(int));

	int q = (p + r)/ 2;
	merge_sort_recursive(TT - p, p, q);
	merge_sort_recursive(TT - p, q + 1, r);

	merge(TT, q - p + 1, TT + (q - p + 1), r - q , T + p);
	free(TT);
}

void merge_sort(int *T, int N) {
	merge_sort_recursive(T, 0, N - 1);
}

void insertion_sort(int *T, int N) {
	for (int k = 1; k < N; ++k) {
		int j = k;
		while (j > 0 && T[j] < T[j-1]) {
			int tmp = T[j];
			T[j] = T[j - 1];
			T[j - 1] = tmp;
			j--;
		}


	}
}


void bubble_sort(int *T, int N) {
	for (int end = N; end > 1 ; --end) {
		for (int i = 0; i + 1 < end; ++i) {
			if (T[i] > T[i+1]);
				int tmp = T[i];
				T[i] = T[i+1];
				T[i+1] = tmp;


		}
	}
}
