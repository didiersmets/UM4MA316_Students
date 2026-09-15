#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"

int main(int argc, char *argv[]){
  srand((unsigned int)time(NULL));
  int N_max = atoi(argv[1]);
  struct Queue *q = queue_init(sizeof(int), 128);
  size_t l_max = queue_length(q);
  for(int i=0; i<N_max; i++){
    int p = rand() % 100 + 1;
    if(p % 2 == 0){
      queue_enqueue(q, &p);
    }
    else {
      void *dest = malloc(sizeof(int));
      queue_dequeue(q, dest);
      free(dest);
    }
    if(l_max < queue_length(q)){
      l_max = queue_length(q);
    }
  }
  printf("%zu\n", l_max);
  queue_dispose(q);
  return EXIT_SUCCESS;
}
