#include "../include/circular_buffer_queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void enlarge_queue_capacity ( struct Queue * q ){
    size_t new_capacity = q->capacity * 2;

    void *new_data = malloc(q->elem_size * new_capacity);
    if(new_data == NULL){
        printf("Error allocating memory!");
        return;
    }

    void *src = (char*)q->data + q->front * q->elem_size;
    size_t size = (q->capacity - q->front) * q->elem_size;

    memcpy(new_data, src, size);

    void *dest = (char*)new_data + size;
    memcpy(dest, q->data, q->front * q->elem_size);

    free(q->data);
    q->data = new_data;
    q->front = 0;
    q->capacity = new_capacity;
}

bool is_empty(const struct Queue *q){
    return q->length == 0;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue * queue_init ( size_t elem_size , size_t capacity ){
    struct Queue* q = malloc(sizeof(struct Queue));

    if(q == NULL){
        printf("Error allocating memory!");
        return NULL;
    }

    q -> data = malloc(elem_size * capacity);
    if(q -> data == NULL){
        printf("Error allocating memory!");
        return NULL;
    }

    q -> front = 0;
    q -> length = 0;
    q -> capacity = capacity;
    q -> elem_size = elem_size;

    return q;
}

void queue_dispose(struct Queue *q){
    if(q!=NULL){
        if(q->data!=NULL){
            free(q->data);
        }
    free(q);
    }    
}

void queue_enqueue ( struct Queue *q , const void * src ){
    if(q -> capacity == q -> length){
        printf("Capacity full! Enlarging the queue.");
        enlarge_queue_capacity(q);
    }

    size_t idx = (q -> front + q -> length) % q -> capacity;

    void *dest = (char*)q->data 
    + (idx * q -> elem_size);

    memcpy(dest, src, q -> elem_size);

    q -> length += 1;
}

void queue_dequeue(struct Queue *q, void *dest) {
    if (q->length == 0) {
        printf("Error, queue empty\n");
        return;
    }
    
    void *src = (char *)q->data + (q->front * q->elem_size);
    
    memcpy(dest, src, q->elem_size);
    
    q->front = (q->front + 1) % q->capacity; 
    q->length -= 1;
}