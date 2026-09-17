#include "../include/circular_buffer_queue.h"

// -- Implementation of the functions in header file circular_buffer_queue.h -- 

//memory allocating function to enlarge the queue
static void enlarge_queue_capacity(struct Queue * q);




bool is_empty(const struct Queue *q){
    return q->length == 0;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue *q = malloc(sizeof(struct Queue)); //allocate the queue in heap
    void *data = malloc(capacity * elem_size); //allocate the space for data in heap

    q->data = data; //pass the data pointer to the data in q

    return q;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    if(q->data != NULL){
        printf("Could not free the data \n");
    }
    free(q);
    if(q != NULL){
        printf("Could not free the data \n");
    }

}

void queue_enqueue(struct Queue *q, const void *src){

    if(q->length == q->capacity){
        //handle the fact that you finished space
    }

    q->length++;
    q->front++;

    // array index to be accessed
    int index = (q->front + q->length) % q->capacity;

    //conversion to byte offset
    size_t byte_offset = (size_t)index * q->elem_size;

    // calculated address and memcpy. Cast to char is just to the sum sums 1 byte * byte_offset
    void* element_ptr = (char*)q->data + byte_offset;
    memcpy(element_ptr, src, q->elem_size);
    q->length++;

}

void queue_dequeue(struct Queue *q, void *dest){

}

static void enlarge_queue_capacity(struct Queue * q){


}