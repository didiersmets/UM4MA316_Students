

struct Priority_data {
    int id;
    float val;
};

struct Priority_queue {
    struct Priority_data *heap;
    int capacity;
    int size;
    int *pos_in_heap;
};

int priority_queue_init(struct Priority_queue *q, int max_id);

void priority_queue_push(struct Priority_queue *q, int id, float val);

struct Priority_data priority_queue_pop(struct Priority_queue *q);

void priority_queue_update(struct Priority_queue *q, int key, float new_val);