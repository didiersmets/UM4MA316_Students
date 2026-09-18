#include <stdlib.h>
#include <stdio.h>
#include  <string.h>

#include "./include/circular_buffer_queue.h"

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

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;

    return q;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
}

void queue_enqueue(struct Queue *q, const void *src){

    if(q->length == q->capacity){
        //handle the fact that you finished space
        enlarge_queue_capacity(q);
    }
    // array index to be accessed
    int index = (q->front + q->length) % q->capacity;

    //conversion to byte offset
    size_t byte_offset = (size_t)index * q->elem_size;

    // calculated address and memcpy. Cast to char is just to the sum sums 1 byte * byte_offset
    void* element_ptr = (char*)q->data + byte_offset;
    //copy the new item 
    memcpy(element_ptr, src, q->elem_size);
    //increase the length
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest){
    if(q->length == 0){ //the queue is already empty
        printf("Dequeue was called althought the queue is empty");
    }else{
        //copy the item do test
        int index = (q->front);
        size_t byte_offset = (size_t)index * q->elem_size;
        void* element_ptr = (char*)q->data + byte_offset;
        memcpy(dest, element_ptr, q->elem_size);

        //"remove" from queue
        q->length--;
        //move the front by 1 address
        //if the front has reached capacity make it 0
        q->front++;
        if (q->front == q->capacity){
            q->front = 0;
        }
    }
}

static void enlarge_queue_capacity(struct Queue * q){

    int new_capacity = q->capacity * 2;


    void *new_data = malloc(new_capacity * q->elem_size);


    //transfer the old data into new data.
    for(int e = 0; e<q->length; e++){
        // array index to be accessed
        int index_q = (q->front + e) % q->capacity;
        int index_new_q = e;

        //conversion to byte offset
        size_t byte_offset_q = (size_t)index_q * q->elem_size;
        size_t byte_offset_new_q = (size_t)index_new_q * q->elem_size;

        // calculated address and memcpy. Cast to char is just to the sum sums 1 byte * byte_offset
        void* element_ptr_q = (char*)q->data + byte_offset_q;
        void* element_ptr_new_q = (char*)new_data + byte_offset_new_q;

        //copy the new item 
        memcpy(element_ptr_new_q, element_ptr_q, q->elem_size);

    }

    //free the old data and put the new pointer in
    free(q->data);
    q->data = new_data;

    q->front = 0;
    q->capacity = new_capacity;

}