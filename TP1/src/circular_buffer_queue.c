#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
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
  return q->length == 0;
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
  size_t rear = (q->front + q->length) % q->capacity;
  void *dest = q->data + rear * q->elem_size;
  memcpy(dest, src, q->elem_size);
  q->length++;
  
}

void queue_dequeue(struct Queue *q, void *dest){
  if(q->length >= 1){
    const void *src = q->data + q->front * q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
  }
}

static void enlarge_queue_capacity(struct Queue *q){
  if(q->length >= q->capacity){
    void *temp = malloc(2 * q->elem_size * q->capacity);
    for(int i=0; i<q->length; i++){
      void *dest =  temp + i * q->elem_size; 
      void *src = q->data + i * q->elem_size;
      memcpy(dest, src, q->elem_size);
    }
    free(q->data);
    q->data = temp;
    q->capacity = 2 * q->capacity;
    q->front = 0;
  }  
}
