#include "circular_buffer_queue.h"
#include <stdlib.h>
#include <string.h>
static void enlarge_queue_capacity(struct Queue *q) {
    size_t new_capacity = q->capacity ? q->capacity * 2 : 1;
    void *new_data = malloc(new_capacity * q->elem_size);
    if (!new_data) exit(EXIT_FAILURE);
    for (size_t i = 0; i < q->length; ++i) {
        size_t idx = (q->front + i) % q->capacity;
        memcpy((char*)new_data + i * q->elem_size,
               (char*)q->data + idx * q->elem_size,
               q->elem_size);
    }
    free(q->data);
    q->data = new_data;
    q->front = 0;
    q->capacity = new_capacity;
}
void queue_init(struct Queue *q, size_t elem_size) {
    q->front = 0;
    q->length = 0;
    q->capacity = 0;
    q->elem_size = elem_size;
    q->data = NULL;
}
void queue_free(struct Queue *q) {
    free(q->data);
    q->data = NULL;
    q->front = q->length = q->capacity = 0;
}
void queue_enqueue(struct Queue *q, const void *elem) {
    if (q->length == q->capacity)
        enlarge_queue_capacity(q);
    size_t idx = (q->front + q->length) % q->capacity;
    memcpy((char*)q->data + idx * q->elem_size, elem, q->elem_size);
    q->length++;
}
void queue_dequeue(struct Queue *q, void *elem) {
    if (q->length == 0) return;
    memcpy(elem, (char*)q->data + q->front * q->elem_size, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
}
int queue_is_empty(const struct Queue *q){
    return q->length == 0;
}
size_t queue_length(const struct Queue *q){
    return q->length;
}