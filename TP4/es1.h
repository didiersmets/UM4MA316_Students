#ifndef ES1_H
#define ES1_H

struct priority_data {
    int id;
    float val;
};

struct priority_queue {
    struct priority_data *heap;
    int capacity;
    int size;
};

// returns 0 on success, -1 if the allocation fails
int priority_queue_init(struct priority_queue *q);

// bigger val = higher priority
void priority_queue_push(struct priority_queue *q, int id, float val);

#endif
