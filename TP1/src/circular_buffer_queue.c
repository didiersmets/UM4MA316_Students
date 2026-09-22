#include"circular_buffer_queue.h"
#include<stdlib.h>
#include<string.h>
static void enlarge_queue_capacity(struct Queue *q){
	size_t old_capacity = q->capacity;
	size_t new_capacity;
	if(old_capacity==0){
		new_capacity=1;
	}else{
		new_capacity=2*old_capacity;
	}
	void *new_data=malloc(new_capacity * q->elem_size);
	for(size_t i=0; i<q->length; i++){
		size_t old_index=(q->front+i)%old_capacity;
		memcpy((char *)new_data + i*q->elem_size, (char *)q->data + old_index * q->elem_size, q->elem_size);
	}
	free(q->data);
	q->data=new_data;
	q->capacity=new_capacity;
	q->front=0;
}

bool is_empty(const struct Queue *q){
	return q->length==0;
}

size_t queue_length(const struct Queue *q){
	return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
	struct Queue *q=malloc(sizeof(struct Queue));
	q->front=0;
	q->length=0;
	q->capacity=capacity;
	q->elem_size=elem_size;

	if(q->capacity==0){
		q->data=NULL;
	}else{
		q->data=malloc(capacity*elem_size);
		if(q->data==NULL){
			free(q);
			return NULL;
		}
	}
	return q;
}

void queue_dispose(struct Queue *q){
	if(q==NULL){
		return;
	}
	free(q->data);
	free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
	if(q->length==q->capacity){
		enlarge_queue_capacity(q);
	}

	size_t index=(q->front+q->length)%q->capacity;
	memcpy((char *)q->data + index*q->elem_size, src, q->elem_size);
	++q->length;
}

void queue_dequeue(struct Queue *q, void *dest){
	if(q->length==0){
		return;
	}
	void *src =  (char *)q->data+q->front*q->elem_size;
	memcpy(dest, src, q->elem_size);
	q->front=(q->front+1)%q->capacity;
	--q->length;

}


	
















