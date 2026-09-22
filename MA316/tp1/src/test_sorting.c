#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "sorting_algorithmes.h"

#ifndef N_MAX
#define N_MAX 12
#endif

int main() {
  FILE *f;
  int i = 0, j, N[N_MAX] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000};
  int *A_bubblesort, *A_insertionsort, *A_mergesort;
  struct timeval start, end;
  long microseconds_bubblesort, microseconds_insertionsort,
      microseconds_mergesort;

  f = fopen("data_sorting.txt", "w");
  if (f == NULL) {
    printf("Error: Could not open file data_sorting.txt\n");
    return EXIT_FAILURE;
  }

  srand(time(NULL));

  while (i < N_MAX) {
    A_bubblesort = (int *)malloc(N[i] * sizeof(int));
    A_insertionsort = (int *)malloc(N[i] * sizeof(int));
    A_mergesort = (int *)malloc(N[i] * sizeof(int));

    if (!A_bubblesort || !A_insertionsort || !A_mergesort) {
      fclose(f);
      printf("Error allocating memory");
      return EXIT_FAILURE;
    }

    for (j = 0; j < N[i]; j++) {
      A_bubblesort[j] = rand();
      A_insertionsort[j] = rand();
      A_mergesort[j] = rand();
    }

    // Bubble sort
    gettimeofday(&start, NULL);
    bubble_sort(A_bubblesort, N[i]);
    gettimeofday(&end, NULL);
    microseconds_bubblesort =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    // Insertion sort
    gettimeofday(&start, NULL);
    insertion_sort(A_insertionsort, N[i]);
    gettimeofday(&end, NULL);
    microseconds_insertionsort =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    // Merge sort
    gettimeofday(&start, NULL);
    merge_sort(A_mergesort, 0, N[i]);
    gettimeofday(&end, NULL);
    microseconds_mergesort =
        (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    fprintf(f, "%d\t%ld\t%ld\t%ld\n", N[i], microseconds_bubblesort,
            microseconds_insertionsort, microseconds_mergesort);

    free(A_bubblesort);
    free(A_insertionsort);
    free(A_mergesort);
    i++;
  }

  fclose(f);
  return 0;
}