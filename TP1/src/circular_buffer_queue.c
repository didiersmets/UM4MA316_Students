#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/circular_buffer_queue.h"

static void enlarge_queue_capacity(struct Queue *q);

struct Queue *queue_init(size_t elem_size, size_t capacity){
  struct Queue *q = malloc(sizeof(struct Queue));
  q->front = 0;
  q->length = 0;
  q->capacity = capacity;
  q->elem_size = elem_size;
  q->data = malloc(elem_size * capacity);
  return q;
}

bool is_empty(const struct Queue *q){
  if(q->length == q->capacity){
    return True;
  }
  return False;
}

size_t queue_length(const struct Queue *q){
  return q->length;
}

void queue_dispose(struct Queue *q){
  free(q->data);
  free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
  enlarge_queue_capacity(q);
  size_t 
  void *dest = é 
  memcpy(dest, src, q->elem_size);  
  
}

void queue_dequeue(struct Queue *q, void *dest){

}

static void enlarge_queue_capacity(struct Queue *q){

}
