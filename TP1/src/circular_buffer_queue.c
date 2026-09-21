#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer_queue.h"

bool is_empty(const struct Queue *q) {
return q->length == 0;
}

size_t queue_length(const struct Queue *q) 
return q->length;

struct Queue *queue_init(size_t elem_size, size_t capacity) {

	struct Queue  *q= malloc(sizeof(struct Queue));
        if (q == NULL) {
		return NULL;
}

q->front = 0;
q->length = 0;
q->capacity = capacity;
q->elem_size = elem_size;

q->data = malloc(capacity *elem_size);
if (q->data == NULL) {
free(q);
return NULL;
}
return q;

} 

void queue_dispose(struct Queue *q) {
if (q != NULL) {
free(q->data);
free(q);
}
}

static void enlarge_queue_capacity(struct Queue *q) {

size_t new_capacity = (q->capacity == 0) ? 1 : q->capacity * 2;

void *new_data = malloc(new_capacity * q->elem_size);

void queue_enqueue(struct Queue *q, const void *src) {
if 




}


void queue_dequeue(struct Queue *q, void *dest) {


