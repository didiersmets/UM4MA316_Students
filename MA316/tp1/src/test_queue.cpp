#include "include/circular_buffer_queue.hpp"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *f;
  Queue<int> *queue;
  int q, n, p, i, j = 1;
  size_t l_max = 0;

  if (argc != 3) {
    printf("Usage: %s <integer positive number> <integer positive number>\n",
           argv[0]);
    return 1;
  }

  q = atoi(argv[1]);
  n = atoi(argv[2]);
  if (q < 0 || n < 1) {
    printf("Error: Please provide two positive integers.\n");
    return 1;
  }

  f = fopen("data_c++.txt", "w");
  if (f == NULL) {
    printf("Error: Could not open file data.txt\n");
    return 1;
  }

  while (j < n) {
    queue = new Queue<int>(q);
    i = 0;
    l_max = 0;
    while (i < j) {
      p = rand();
      if ((p % 2) == 0) {
        queue->queue_enqueue(p);
      } else {
        queue->queue_dequeue(p);
      }
      if (l_max < queue->queue_length()) {
        l_max = queue->queue_length();
      }
      i++;
    }
    fprintf(f, "%d\t%ld\n", j, l_max);
    delete queue;
    j++;
  }

  fclose(f);
  return l_max;
}