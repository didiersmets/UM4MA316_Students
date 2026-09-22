#include <stdio.h>
#include <stdlib.h>

// private functions

void merge(int *A, int sA, int *B, int sB, int *C) {
  int idxA = 0, idxB = 0, idxC;

  for (idxC = 0; idxC < sA + sB; idxC++) {
    if ((idxB == sB) || ((idxA < sA) && A[idxA] <= B[idxB])) {
      C[idxC] = A[idxA++];
    } else {
      C[idxC] = B[idxB++];
    }
  }
}

// public functions

void bubble_sort(int *A, int N) {
  int i, j, tmp;

  for (i = 1; i < N; i++) {
    for (j = 0; j < N - i; j++) {
      if (A[j] > A[j + 1]) {
        tmp = A[j];
        A[j] = A[j + 1];
        A[j + 1] = tmp;
      }
    }
  }
}

void insertion_sort(int *A, int N) {
  int i, j, tmp;

  for (i = 1; i < N; i++) {
    j = i;
    while (j > 0 && (A[j] < A[j - 1])) {
      tmp = A[j];
      A[j] = A[j - 1];
      A[j - 1] = tmp;
      j--;
    }
  }
}

void merge_sort(int *A, int p, int N) {
    int q;

    if(p<N){
        q = (p+N)/2;
        mergesort(A, p, q);
        mergesort(A, q+1, N);
        // mergesort();
    }
}