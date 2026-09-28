#include <stdlib.h> // for malloc, free
#include "sorting.h"


bool is_sorted(const int *T, int N) {
	for (int i = 0; i + 1 < N; i++) {
		if (T[i] > T[i + 1]) {
			return false;
		}
	}
	return true;
}


void bubble_sort(int *T, int N) {
	for (int end = N; end > 1; end--) {
		for (int i = 0; i + 1 < end; i++) {

		}
	}
}


void insertion_sort(int *T, int N) {
	for (int k = 1; k < N; k++) {
		int j = k;

	}
}

