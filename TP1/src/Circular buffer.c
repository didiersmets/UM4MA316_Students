#include<stdio.h>
#include<stdlib.h>
#include "../include/circular_buffer_queue.h"
#include<string.h>

static void enlarge_queue_capacity(struct Queue *q){
    if (q -> capacity > 0){
        int n = 2 * q -> capacity ;
        q->data = realloc(q->data,n);
    }else{
        q->data = realloc(q->data,1);
    }
}


bool is_empty(const struct Queue *q)
{
    return q->length == 0;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue * q = malloc(capacity * sizeof(struct Queue));
    q -> front = 0;
    q -> length = 0;
    q -> capacity = capacity;
    
    return q;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
    if (q->length == q->capacity){
        enlarge_queue_capacity(q);
    }
    void *dest = (char *)q->data + ((q->front + q->length)%q->capacity)*q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->length++;

    
}

void queue_dequeue(struct Queue *q, void *dest){
    if (q->length == 0){
        return ;
    }
    void* src = (char*)q->data + q->front * q->elem_size;
    memcpy(dest,src,q->elem_size);
    q->front = (q->front + 1)%(q->capacity);

    q->length--;
}


