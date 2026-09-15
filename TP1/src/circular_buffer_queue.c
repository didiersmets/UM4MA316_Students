#include<stdio.h>
#include<string.h>
static void enlarge_queue_capacity(struct Queue *q){
	size_t old_cap=q->capacity;
	if(old_cap==0){
		q->capacity=1;
	}
	q->capacity=2*old_cap;
	void new_data=malloc(q->capacity*q->elem_size);
	for(size_t i=0; i<old_cap; i++){


bool is_empty(const struct Queue *q){
	if(q->length==0){
		return True;
	}
	return False;
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
	q->data=malloc(capacity*elem_size);
	return q;
}

void queue_dispose(struct Queue *q){
	free(q->data);
	free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
	if(q->length==q->capacity){


