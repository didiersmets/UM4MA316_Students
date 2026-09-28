#ifndef CIRCULAR_BUFFER_QUEUE_H
#define CIRCULAR_BUFFER_QUEUE_H

#include <stdbool.h>
#include <stddef.h> // for size_t


struct Queue {
	size_t front; 
	size_t length; 
	size_t capacity; 
	size_t elem_size; 
	void *data; 
};

bool is_empty(const struct Queue *q);
size_t queue_length(const struct Queue *q);
struct Queue *queue_init(size_t elem_size, size_t capacity);
void queue_dispose(struct Queue *q);
void queue_enqueue(struct Queue *q, const void *src);
void queue_dequeue(struct Queue *q, void *dest);

#endif
