#include "../include/circular_buffer_queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void enlarge_queue_capacity ( struct Queue * q ){
    printf("enlarge_queue_capacity not implemented yet !");
}

bool is_empty(const struct Queue *q) {
    if (q->length > 0) {
        return false;
    }
    else {
        return true;
    }
}

size_t queue_length(const struct Queue *q) {
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity) {
    
    void *data_ptr = malloc(capacity * elem_size);

    static struct Queue q;
    q.front = 0;
    q.length = 0;
    q.capacity = capacity;
    q.elem_size = elem_size;
    q.data = data_ptr;

    return &q;
}

void queue_dispose(struct Queue *q) {
    free(q->data);
}

void queue_enqueue(struct Queue *q, const void *src) {
    // TODO : ajouter cas de ring buffer rempli (if length == capacity)
    if (q->length==q->capacity) {
        enlarge_queue_capacity(q);
    }

    void *dest = q-> data;
    dest = memcpy(dest + sizeof(int)*q->length, src, sizeof(int));
    q->length+=1;
}

void queue_dequeue(struct Queue *q, void *dest) {
    if (is_empty(q)) {
        puts("Queue is empty, can not dequeue!");
    }
    else {
        void *src = q-> data;
        dest = memcpy(dest, src + sizeof(int) * q->front, sizeof(int));
        q->front +=1;
        q->length-=1;
    }
    
}