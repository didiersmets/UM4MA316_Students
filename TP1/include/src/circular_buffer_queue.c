#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void enlarge_queue_capacity(struct Queue *q);

static void enlarge_queue_capacity(struct Queue *q){

    if((q->capacity)==(q->length)){
        size_t new_cap = q->capacity == 0 ? 1 : 2 * q->capacity;
        q->data = realloc(q->data, new_cap * q->elem_size);
        q->capacity = new_cap;    
    }
}



bool is_empty(const struct Queue *q){

    return q->length==0;
}

size_t queue_length(const struct Queue *q){

    return  q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity)
{
    struct Queue *q = malloc(sizeof(struct Queue));
    q->elem_size = elem_size;
    if (capacity > 0) {
        q->data = malloc(capacity * elem_size);
    }
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->front = 0;
    q->length = 0;
    return q;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q)
}

void queue_enqueue(struct Queue *q, const void *src){
    void *dest = (char *)q->data + ((q->front + q->size) % q-capacity)*q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest){
    if (q->length == 0)
        return;
    void *src = ;
    memcpy(dest,src,q->elem_size);
    q->length--;
}
