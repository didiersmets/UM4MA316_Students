#include <stdbool.h>
#include <stddef.h> // for size_t
#include <string.h>
#include <assert.h>


struct Queue {
	size_t front; // index of the first element in the queue
	size_t length; // number of items presently in the queue
	size_t capacity; // capacity of the queue (in nbr of items)
	size_t elem_size; // length in bytes of each item in the queue
	void *data; // address of the array
};

bool is_empty(const struct Queue *q); {
	assert(q != NULL);
	return (q->size == 0);
	}

size_t queue_length(const struct Queue *q); {
	assert(q != NULL);
	return (q->size);
}


struct Queue *queue_init(size_t elem_size, size_t capacity);
	struct Queue *q = malloc(sizeof(Queue));
	if (q != NULL) {
		q->size = 0
		q->capacity = 0
		q->data = NULL
	}


void queue_dispose(struct Queue *q);
	if (q == NULL) {
		return
	}
	free(q->data);
	free(s);

void queue_enqueue(struct Queue *q, const void *src);
	if (q->length == q->capacity) {
		enlarge_queu_capacity(q);
	}
	void *dest = (char*)(q->data) + ((q->front + q->length) % q->capacity) * (q->elem_size);

	memcpy(dest, src , q->elem_size);

	q->length = q->length + 1



void queue_dequeue(struct Queue *q, void *dest);
	if (q->is_empty) {
		perror ("Queue is empty");
		return;
	}

	void *src = (char*)(q->data) + ((q->front + 1) % q->capacity) * (q->elem_size);

	q->length = q->length - 1


static void enlarge_queu_capacity(struct Queue *q, void *q);

	size_t old_cap = q >capacity
	size_t new_cap = old_cap + 1
	int *new_data = realloc(q->data, new_cap * q->elem_size);
	if (new_data != NULL) {
		return;
	}
	q->data = new_data;
	q->capacity = new_cap;








