// A source file for an array based implementation of a Circular Buffer Queue
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/circular_buffer_queue.h"


struct Queue *queue_init(size_t elem_size, size_t capacity)
{
    struct Queue *q = malloc(sizeof(struct Queue));
    if(q != NULL) {

        q -> data = malloc(capacity * elem_size);

        if(q -> data == NULL){
            free(q);
            return NULL;
        }

        q -> length = 0;
        q -> elem_size = elem_size;
        q -> capacity = capacity;
        q -> front = 0;
        
    }
    return q;
}

bool is_empty(const struct Queue *q){
    return q -> length == 0;
}

size_t queue_length(const struct Queue *q){
    return q -> length;
}

void queue_dispose(struct Queue *q){
    if(q == NULL){
        return;
    }
    free(q -> data);
    free(q);
}


static void enlarge_queue_capacity(struct Queue *q){
    if(q -> length < q -> capacity){
        return;
    }
    size_t new_cap = q -> capacity == 0 ? 1 : 2*q -> capacity;
    void *new_memory = malloc(new_cap * q->elem_size);

    for(int i=0; i < q->length; i++){
        size_t circular_idx = (q->front + i) % q->capacity;
        void *old_adress = (char*)q->data + (q->elem_size * circular_idx);
        void *new_adress = (char*)new_memory + (q->elem_size * i);
        memcpy(new_adress, old_adress, q->elem_size);
    }

    free(q->data);
    q -> data = new_memory;
    q -> capacity = new_cap;
    q -> front = 0;

}

void queue_enqueue(struct Queue *q, const void *src)
{
    assert(q != NULL);
    if(q -> length == q->capacity){
        enlarge_queue_capacity(q);
    }
    size_t tail_queue_index = (q -> front + q -> length) % (q -> capacity);
    void *dest = (char*)q -> data + tail_queue_index * (q -> elem_size);
    memcpy(dest, src, q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest)
{
    assert(q != NULL);
    assert(dest != NULL);
    if(is_empty(q)){
        return;
    };
    void *front_queue_adress = (char*)q -> data + (q -> front) * (q -> elem_size); 
    memcpy(dest, front_queue_adress, q->elem_size);
    q -> front = (q -> front + 1) % q -> capacity;
    q -> length = q -> length - 1;


}



