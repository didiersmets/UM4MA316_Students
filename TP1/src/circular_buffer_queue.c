#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <assert.h>
#include "circular_buffer_queue.h"

static void enlarge_queue_capacity(struct Queue *q);


bool is_empty(const struct Queue *q) {
	assert(q != NULL);
	return (q->length == 0);
}

size_t queue_length(const struct Queue *q) {
	assert(q != NULL);
	return (q->length);
}


struct Queue *queue_init(size_t elem_size, size_t capacity) {
	struct Queue *q = malloc(sizeof(struct Queue));
	if (q != NULL) {
		q->front = 0;                            
		q->length = 0;
		q->capacity = capacity;                  
		q->elem_size = elem_size;                
		q->data = malloc(capacity * elem_size);  
		if (q->data == NULL && capacity > 0) {   
			free(q);                            
			return NULL;                       
		}
	}
	return q;
}


void queue_dispose(struct Queue *q) {
	if (q == NULL) {
		return;
	}
	free(q->data);
	free(q);
}

void queue_enqueue(struct Queue *q, const void *src) {
	if (q->length == q->capacity) {
		enlarge_queue_capacity(q);
		if (q->length == q->capacity) {                  
			fprintf(stderr, "Could not enlarge queue\n"); 
			return;                                       
		}
	}
	void *dest = (char*)(q->data) + ((q->front + q->length) % q->capacity) * (q->elem_size);

	memcpy(dest, src , q->elem_size);

	q->length = q->length + 1;
}


void queue_dequeue(struct Queue *q, void *dest) {
	if (is_empty(q)) {
		fprintf(stderr, "Queue is empty\n");  
		return;
	}

	void *src = (char*)(q->data) + q->front * (q->elem_size);  

	memcpy(dest, src, q->elem_size);          

	q->front = (q->front + 1) % q->capacity;  
	q->length = q->length - 1;
}


static void enlarge_queue_capacity(struct Queue *q) {
	size_t old_cap = q->capacity;
	size_t new_cap = old_cap + 1;  
	void *new_data = realloc(q->data, new_cap * q->elem_size); 
	if (new_data == NULL) { 
		return;
	}
	q->data = new_data;


	if (q->front + q->length > old_cap) {
		memmove((char*)(q->data) + (q->front + 1) * q->elem_size,  
		        (char*)(q->data) + q->front * q->elem_size,        
		        (old_cap - q->front) * q->elem_size);              
		q->front = q->front + 1;
	}

	q->capacity = new_cap;
}
