#include "standard_heap_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int priority_queue_init(struct Priority_queue *q) {

    q -> heap = malloc(sizeof(struct Priority_data));
    if(q -> heap == NULL) {
        return -1;
    }
    q -> capacity = 1;
    q -> size = 0;

    return 0;
}

// bigger priority value = highest priority
void priority_queue_push(struct Priority_queue *q, int id, float val) {

    if(q -> size == q -> capacity) {
        q -> capacity = q -> capacity * 2;
        struct Priority_data *tmp = realloc(q -> heap, q -> capacity 
                                            * sizeof(struct Priority_data));
        if(tmp == NULL) {
            printf("error increasing priority queue capacity\n");
            return;
        }
        q -> heap = tmp;
    }

    struct Priority_data new_node = { .id = id, .val = val };
    q -> heap[q -> size] = new_node;

    int curr_idx = q -> size;
    int tmp_idx = q -> size - 1;
    int parent = (q -> size - 1) / 2;
    
    while(tmp_idx != -1 && new_node.val > q -> heap[parent].val) {
        struct Priority_data tmp = q -> heap[parent];
        q -> heap[parent] = new_node;
        q -> heap[curr_idx] = tmp;
        curr_idx = parent;
        tmp_idx = parent - 1;
        parent = tmp_idx / 2;
    }
    
    q -> size++;
}

struct Priority_data priority_queue_pop(struct Priority_queue *q) {

    struct Priority_data extracted = q -> heap[0];
    q -> size--;
    q -> heap[0] = q -> heap[q -> size];

    int curr_idx = 0;
    if(curr_idx * 2 + 1 >= q -> size) return extracted;

    int idx_max;
    if(curr_idx * 2 + 2 >= q -> size) {
        idx_max = curr_idx * 2 + 1;
    } else {
        idx_max = (q -> heap[curr_idx * 2 + 1].val > q -> heap[curr_idx * 2 + 2].val) ? 
                    curr_idx * 2 + 1 : curr_idx * 2 + 2;
    }

    while(curr_idx * 2 + 2 < q -> size && q -> heap[curr_idx].val < q -> heap[idx_max].val) {
        struct Priority_data tmp = q -> heap[idx_max];
        q -> heap[idx_max] = q -> heap[curr_idx];
        q -> heap[curr_idx] = tmp;
        curr_idx = idx_max;
        if(curr_idx * 2 + 1 >= q -> size) return extracted;
        if(curr_idx * 2 + 2 >= q -> size) {
            idx_max = curr_idx * 2 + 1;
        } else {
            idx_max = (q -> heap[curr_idx * 2 + 1].val > q -> heap[curr_idx * 2 + 2].val) ? 
                        curr_idx * 2 + 1 : curr_idx * 2 + 2;
        }
    }

    return extracted;
}

void priority_queue_update(struct Priority_queue *q, int key, float new_val) {
    
}