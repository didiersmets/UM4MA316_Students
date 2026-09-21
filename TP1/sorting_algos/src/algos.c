#include "../include/algos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void bubble_sort(int *array_to_sort, int elem_nb) {
  for (int j=1; j<elem_nb; j++) {
    for (int i=0; i<elem_nb-1; i++) {
      if (array_to_sort[i] > array_to_sort[i+1]) {
        int tmp = array_to_sort[i];
        array_to_sort[i] = array_to_sort[i+1];
        array_to_sort[i+1] = tmp;
      }
    }
  }  
}

void insertion_sort(int *array_to_sort, int elem_nb) {

  for (int i = 1; i < elem_nb; i++) {

        int j = i;

        while (j != 0 && array_to_sort[j] < array_to_sort[j-1]) {

            int tmp = array_to_sort[j-1];
            array_to_sort[j-1] = array_to_sort[j];
            array_to_sort[j] = tmp;

            j--;
        }
    }
}

void merge(int *T, int *S, int p, int q, int r) {
  int i = p;
  int j = q+1;
  int k = p;

  while (i <= q && j <= r) {
    if (S[i] <= S[j]) {
      T[k] = S[i];
      i++;
    }
    else {
      T[k] = S[j];
      j++;
    }
    k++;
  }
  while (i <= q) {
    T[k] = S[i];
    i++;
    k++;
  }
  while (j <= r) {
    T[k] = S[j];
    j++;
    k++;
  }
}

void recursive_merge_loop(int *T, int *S, int p, int r) {
  if (p < r) {
    int q = (p+r)/2;
    recursive_merge_loop(S, T, p, q);
    recursive_merge_loop(S, T, q+1, r);
    merge(T, S, p, q, r);
  }
}

void merge_sort(int *array_to_sort, int elem_nb) {
  int *S = malloc(sizeof(int) * (size_t)elem_nb);
  memcpy(S, array_to_sort, sizeof(int) * (size_t)elem_nb);
  recursive_merge_loop(array_to_sort, S, 0, elem_nb-1);
  free(S);
}
