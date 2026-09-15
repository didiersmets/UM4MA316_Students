#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer_queue.h"


static void enlarge_queue_capacity(struct Queue *q);

bool is_empty(const struct Queue *q){
    return q->length == 0;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue* queue = malloc(sizeof(struct Queue));
    void *data = malloc(elem_size * capacity);
    queue -> front = 0; // index of the first element in the queue
	queue -> length = 0; // number of items presently in the queue
	queue -> capacity = capacity; // capacity of the queue (in nbr of items)
	queue -> elem_size = elem_size; // length in bytes of each item in the queue
	queue -> data = data; // address of the array
    return queue;
}

void queue_dispose(struct Queue *q){
    if (q == NULL) return;
    free(q->data);
    free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
    if (q->length == q->capacity){
        enlarge_queue_capacity(q);
    }
    size_t tail = (q->front + q->length) % q->capacity;
    void *dest = (char *)q->data + tail * q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest){
    if (q->length == 0) return;
    void *src = (char *)q->data + q->front * q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
}

static void enlarge_queue_capacity(struct Queue *q){
    size_t newcapacity = q->capacity + 1;
    void *newdata = malloc(q->elem_size * newcapacity);

    for (size_t i = 0; i < q->length; i++) {
        size_t old_index = (q->front + i) % q->capacity;
        void *src = (char *)q->data + old_index * q->elem_size;
        void *dest = (char *)newdata + i * q->elem_size;;
        memcpy(dest, src, q->elem_size);
    }

    free(q->data);
    q->data = newdata;
    q->capacity = newcapacity;
    q->front = 0;
}