#ifndef CIRCULAR_BUFFER_QUEUE_H
#define CIRCULAR_BUFFER_QUEUE_H
#include <stddef.h>
struct Queue {
    size_t front;      // index of the first element
    size_t length;     // number of items currently in the queue
    size_t capacity;   // capacity in number of items
    size_t elem_size;  // size in bytes of one item
    void *data;        // address of the array
};
void queue_init(struct Queue *q, size_t elem_size);
void queue_free(struct Queue *q);
void queue_enqueue(struct Queue *q, const void *elem);
void queue_dequeue(struct Queue *q, void *elem);
int  queue_is_empty(const struct Queue *q);
size_t queue_length(const struct Queue *q);
#endif