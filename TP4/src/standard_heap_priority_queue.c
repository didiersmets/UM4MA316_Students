#include "standard_heap_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int priority_queue_init(struct Priority_queue *q, int max_id) {

    q -> heap = malloc(sizeof(struct Priority_data));
    if(q -> heap == NULL) {
        return -1;
    }
    q -> capacity = 1;
    q -> size = 0;

    q -> pos_in_heap = malloc((max_id + 1) * sizeof(int));
    if(q -> pos_in_heap == NULL) {
        return -1;
    }
    for(int i = 0; i < max_id; i++){
        q -> pos_in_heap[i] = -1;
    }

    return 0;
}

static void swap(struct Priority_queue *q, int pos1, int pos2) {

    int tmp_pos = q -> pos_in_heap[q -> heap[pos1].id]; 
    q -> pos_in_heap[q -> heap[pos1].id] = q -> pos_in_heap[q -> heap[pos2].id];
    q -> pos_in_heap[q -> heap[pos2].id] = tmp_pos;

    struct Priority_data tmp_data = q -> heap[pos1];
    q -> heap[pos1] = q -> heap[pos2];
    q -> heap[pos2] = tmp_data;
}

static void sift_up(struct Priority_queue *q, int pos) {
    int curr_idx = pos;
    int tmp_idx = pos - 1;
    int parent = (pos - 1) / 2;
    
    while(tmp_idx != -1 && q -> heap[curr_idx].val > q -> heap[parent].val) {
        swap(q, curr_idx, parent);
        curr_idx = parent;
        tmp_idx = parent - 1;
        parent = tmp_idx / 2;
    }
}

static void sift_down(struct Priority_queue *q, int pos) {
    int curr_idx = 0;
    if(curr_idx * 2 + 1 >= q -> size) return;

    int idx_max;
    if(curr_idx * 2 + 2 >= q -> size) {
        idx_max = curr_idx * 2 + 1;
    } else {
        idx_max = (q -> heap[curr_idx * 2 + 1].val > q -> heap[curr_idx * 2 + 2].val) ? 
                    curr_idx * 2 + 1 : curr_idx * 2 + 2;
    }

    while(curr_idx * 2 + 2 < q -> size && q -> heap[curr_idx].val < q -> heap[idx_max].val) {
        swap(q, curr_idx, idx_max);
        curr_idx = idx_max;
        if(curr_idx * 2 + 1 >= q -> size) return;
        if(curr_idx * 2 + 2 >= q -> size) {
            idx_max = curr_idx * 2 + 1;
        } else {
            idx_max = (q -> heap[curr_idx * 2 + 1].val > q -> heap[curr_idx * 2 + 2].val) ? 
                        curr_idx * 2 + 1 : curr_idx * 2 + 2;
        }
    }
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
    q -> pos_in_heap[id] = q -> size;

    sift_up(q, q -> size);
    
    q -> size++;
}

struct Priority_data priority_queue_pop(struct Priority_queue *q) {

    struct Priority_data extracted = q -> heap[0];
    q -> pos_in_heap[extracted.id] = -1;
    q -> size--;
    q -> heap[0] = q -> heap[q -> size];
    q -> pos_in_heap[q -> heap[0].id] = 0;

    sift_down(q, 0);

    return extracted;
}

void priority_queue_update(struct Priority_queue *q, int key, float new_val) {
    if(new_val > q -> heap[q -> pos_in_heap[key]].val) {
        q -> heap[q -> pos_in_heap[key]].val = new_val;
        sift_up(q, q -> pos_in_heap[key]);
    } else if(new_val < q -> heap[q -> pos_in_heap[key]].val) {
        q -> heap[q -> pos_in_heap[key]].val = new_val;
        sift_down(q, q -> pos_in_heap[key]);
    }
}