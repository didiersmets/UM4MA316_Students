#include "circular_buffer_queue.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private functions

static void enlarge_queue_capacity(struct Queue *q) {
  size_t new_capacity, first_part_len, second_part_len;
  void *new_data;
  char *src_ptr, *first_src_ptr, *second_dst_ptr;

  new_capacity = q->capacity * 2;

  new_data = static_cast<T*>(malloc(new_capacity * sizeof(T)));
  if (!new_data) {
    printf("Error allocating memory\n");
    return;
  }

  src_ptr = (char *)q->data + (q->front * q->elem_size);
  if (q->front + q->length <= q->capacity) {
    memcpy(new_data, src_ptr, q->length * q->elem_size);
  } else {
    // Wrap-around
    first_part_len = q->capacity - q->front;
    second_part_len = q->length - first_part_len;

    first_src_ptr = (char *)q->data + (q->front * q->elem_size);
    memcpy(new_data, first_src_ptr, first_part_len * q->elem_size);

    second_dst_ptr = (char *)new_data + (first_part_len * q->elem_size);
    memcpy(second_dst_ptr, q->data, second_part_len * q->elem_size);
  }

  free(q->data);
  q->data = new_data;
  q->capacity = new_capacity;
  q->front = 0;
}

static bool is_full(struct Queue *q) { return q->length == q->capacity; }

// Public functions

bool is_empty(const struct Queue *q) { return q->length == 0; }

size_t queue_length(const struct Queue *q) { return q->length; }

struct Queue *queue_init(size_t elem_size, size_t capacity) {
  struct Queue *q;

  if (elem_size < 1 || capacity < 1) {
    return NULL;
  }

  q = malloc(sizeof *q);
  if (!q) {
    return NULL;
  }

  q->data = malloc(capacity * elem_size);
  if (!q->data) {
    free(q);
    return NULL;
  }

  // Initialize q values

  q->front = 0;
  q->length = 0;
  q->capacity = capacity;
  q->elem_size = elem_size;

  return q;
}

void queue_dispose(struct Queue *q) {
  free(q->data);
  free(q);
}

void queue_enqueue(struct Queue *q, const void *src) {
  size_t tail;
  char *dest;

  if (!q) {
    return;
  }

  if (is_full(q)) {
    enlarge_queue_capacity(q);
  }

  tail = (q->front + q->length) % q->capacity;
  dest = (char *)q->data + (tail * q->elem_size);
  memcpy(dest, src, q->elem_size);

  (q->length)++;
}

void queue_dequeue(struct Queue *q, void *dest) {
  char *src;

  if (!q || is_empty(q)) {
    return;
  }

  src = (char *)q->data + (q->front * q->elem_size);
  memcpy(dest, src, q->elem_size);

  q->front = (q->front + 1) % (q->capacity);
  (q->length)--;

  return;
}
