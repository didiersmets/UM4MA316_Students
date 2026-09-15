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
    assert(!is_empty(q));
    void *front_queue_adress = (char*)q -> data + (q -> front) * (q -> elem_size); 
    memcpy(dest, front_queue_adress, q->elem_size);
    q -> front = (q -> front + 1) % q -> capacity;
    q -> length = q -> length - 1;


}



