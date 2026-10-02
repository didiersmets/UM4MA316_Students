#include <stdbool.h>
#include <stddef.h> // for size_t
#include "circular_buffer_queue.h"

static void enlarge_queue_capacity (struct Queue * q){
    size_t newCapacity = q->capacity * 2;

    void *newData = malloc(q->elem_size * new_capacity);
    if(newData == NULL){
        printf("Erorr allocating memory!");
        return;
    }
    void *src = (char*)q->data + q->front * q->elem_size;
    size_t size = (q->capacity - q->front) * q->elem_size;

    memcpy(newData, src, size);

    void *dest = (char*)newData + size;
    memcpy(dest, q->data, q->front * q->elem_size);

    free(q->data);
    q->data = newData;
    q->front = 0;
    q->capacity = newCapacity;
}

bool is_empty(const struct Queue *q){
    return q->length == 0;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){

    struct Queue *q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        printf("Error allocating memory!");
        return NULL; 
    }
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;

    q->data = malloc(elem_size * capacity);
    if (q->data == NULL) {
        printf("Error allocating memory!");
        return NULL; 
    }
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


void queue_enqueue(struct Queue *q, const void *src){
    if (q->length == q->capacity) {
        printf("The capacity is full: queue enlarged"); 
        enlarge_queue_capacity(q);
    }

    size_t index = (q->front + q->length) % q->capacity;
    
    void *dest = (char *)q->data + index*q->elem_size;
    memcpy(dest, src, q->elem_size);

    q->length++;
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