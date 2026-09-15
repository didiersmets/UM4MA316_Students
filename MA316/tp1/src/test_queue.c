#include "circular_buffer_queue.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *f;
  struct Queue *queue;
  int q, n, p, i, l_max, j = 1;

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

  f = fopen("data.txt", "w");
  if (f == NULL) {
    printf("Error: Could not open file data.txt\n");
    return 1;
  }

  while (j < n) {
    queue = queue_init(sizeof(int), q);
    if (!q) {
      printf("Error initiating the queue\n");
      fclose(f);
      return 1;
    }
    i = 0;
    l_max = 0;
    while (i < j) {
      p = rand();
      if ((p % 2) == 0) {
        queue_enqueue(queue, &p);
      } else {
        queue_dequeue(queue, &p);
      }
      if (l_max < queue->length) {
        l_max = queue->length;
      }
      i++;
    }
    fprintf(f, "%d\t%d\n", j, l_max);
    queue_dispose(queue);
    j++;
  }

  fclose(f);
  return l_max;
}