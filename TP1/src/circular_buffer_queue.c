#include <stdbool.h>
#include <stddef.h> // for size_t
#include "circular_buffer_queue.h"

bool is_empty(const struct Queue *q){
    return q->length == 0;
}

size_t queue_length(const struct Queue *q){
    return q-> elem_size * q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){

    struct Queue *q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        return NULL; 
    }
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->data = malloc(elem_size * capacity);
    if (q->data == NULL) {
        free(q); 
        return NULL; 
    }
    return q;   
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
}


void queue_enqueue(struct Queue *q, const void *src){
    if (q->length == q->capacity) {
        return; 
    }

    size_t index = (q->front + q->length) % q->capacity;
    memcpy((char *)q->data + index*q->elem_size, src, q->elem_size);
    q->length++;
}