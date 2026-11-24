struct priority_data {
	int id;
	float val;
};

struct priority_queue {
	struct priority_data *heap;
	int capacity;
	int size;
};

int priority_queue_init(struct priority_queue *q) {
	int i = q->heap[q->size-1];
	return i;
}

void priority_queue_push(struct priority_queue *q, int id, float val){
	if (q->capacity == 0){
		q->capacity = 1;
	}

	if(q->capacity == q->size){
		q->capacity = 2*q->capacity;
	}

	struct priority_data new;
	new->id = id;
	new->val = val;

	q->heap
