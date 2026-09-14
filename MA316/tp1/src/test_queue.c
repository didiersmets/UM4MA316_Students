#include "circular_buffer_queue.h"

#include <stdlib.h>

int main(int argc, char **argv) {
  struct Queue *q;
  int q, p, i;

  if (argc != 2) {
    printf("Usage: %s <integer positive number>\n", argv[0]);
    return 1;
  }

  q = atoi(argv[1]);
  if (q < 0) {
    printf("Error: Please provide a positive integer.\n");
    return 1;
  }

  q = queue_init(sizeof(int), q);

  i = 0;
  while (i < q) {
    p = rand();
    if ((p % 2) == 0) {
      queue_enqueue(q, p);
    }

    else {
    }

    i++;
  }

  return 0;
}