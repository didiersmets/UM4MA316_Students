#ifndef SORTING_H
#define SORTING_H

#include <stdbool.h>

void bubble_sort(int *T, int N);
void insertion_sort(int *T, int N);
void merge_sort(int *T, int N);

bool is_sorted(const int *T, int N);

#endif
