#include "../include/circular_buffer_queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool is_empty(const struct Queue *q) {
    return q->length == 0;
}

size_t queue_length(const struct Queue *q) {
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity) {
    struct Queue *q = malloc(sizeof(struct Queue));

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->data = malloc(capacity * elem_size);
}

void queue_dispose(struct Queue *q) {
    
    q->front = 0;
    q->length = 0;

}

static void enlarge_queue_capacity(struct Queue *q) {;

    struct Queue *tmp = queue_init(q->elem_size, q->capacity * 2);
    tmp->data = malloc(q->capacity * 2 * q->elem_size);

    memcpy(tmp->data, (char*)q->data + q->front * q->elem_size, q->elem_size 
            * (q->length - q->front));
    memcpy((char*)tmp->data + q->elem_size * (q->length - q->front), q->data, q->elem_size 
            * q->front);

    free(q);
    *q = *tmp;

}

void queue_enqueue(struct Queue *q, const void *src) {

    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }

    size_t index = (q->front + q->length) % q->capacity;
    memcpy((char*)q->data + index * q->elem_size, src, q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest) {

    if(q->length == 0) {
        printf("Cannot dequeue, the queue is empty\n");
        return;
    }

    memcpy(dest, (char*)q->data + q->front * q->elem_size, q->elem_size);
    
    q->front = (q->front + 1) % q->capacity;

    q->length--;
    return;
}