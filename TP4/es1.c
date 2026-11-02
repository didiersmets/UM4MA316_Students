#include <stdio.h>
#include <stdlib.h>
#include "es1.h"

int priority_queue_init(struct priority_queue *q) {
    q->heap = malloc(sizeof(struct priority_data));
    if (q->heap == NULL) {
        q->capacity = 0;
        q->size = 0;
        return -1;
    }
    q->capacity = 1;
    q->size = 0;
    return 0;
}

static void swap(struct priority_queue *q, int pos1, int pos2) {
    struct priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;
}

// moves the element at pos up while it is bigger than its parent
static void sift_up(struct priority_queue *q, int pos) {
    int i = pos;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (q->heap[i].val <= q->heap[parent].val)
            break;
        swap(q, i, parent);
        i = parent;
    }
}

void priority_queue_push(struct priority_queue *q, int id, float val) {
    if (q->size == q->capacity) {
        int new_capacity = q->capacity > 0 ? 2 * q->capacity : 1;
        struct priority_data *new_heap =
            realloc(q->heap, new_capacity * sizeof(struct priority_data));
        if (new_heap == NULL) {
            printf("Failed to increase the queue capacity\n");
            return;
        }
        q->heap = new_heap;
        q->capacity = new_capacity;
    }

    q->heap[q->size].id = id;
    q->heap[q->size].val = val;
    q->size++;
    sift_up(q, q->size - 1);
}
