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
	
