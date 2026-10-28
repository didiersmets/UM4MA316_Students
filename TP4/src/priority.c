#include "priority.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int priority_queue_init(struct priority_queue *q, int max_id){
    q->capacity = 1;
    q->size = 0;
    q->heap = malloc(q->capacity * sizeof(struct priority_data));
    q->pos_in_heap = malloc((max_id + 1) * sizeof(int));
    for (int i = 0; i <= max_id; i++){
        q->pos_in_heap[i] = -1;
    }
    return 0;
}

static void swap(struct priority_queue *q, int pos1, int pos2){
    struct priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;
    q->pos_in_heap[q->heap[pos1].id] = pos1;
    q->pos_in_heap[q->heap[pos2].id] = pos2;
}

static void sift_up(struct priority_queue *q, int pos){   
    while (pos > 0){
        int parent = (pos-1)/2;
        if (q->heap[parent].val <= q->heap[pos].val){ return;}
        swap(q, parent, pos);
        pos = parent;
    }
}

static void sift_down(struct priority_queue *q, int pos){
    while (1){
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int little = pos;

        if (left < q->size && q->heap[left].val < q->heap[little].val){ little = left;}
        if (right < q->size && q->heap[right].val < q->heap[little].val){ little = right;}
        if (little == pos){ return;}

        swap(q, pos, little);
        pos = little;
    }
}

void priority_queue_push(struct priority_queue *q, int id, float val){

    if (q->size == q->capacity){
        int new = 2 * q->capacity;
        struct priority_data *tmp = realloc(q->heap, new * sizeof(struct priority_data));
        q->heap = tmp;
        q->capacity = new;
    }
    int pos = q->size;
    q->heap[pos].id = id;
    q->heap[pos].val = val;
    q->pos_in_heap[id] = pos;
    q->size++;
    sift_up(q, pos);
}

struct priority_data priority_queue_pop(struct priority_queue *q){
    struct priority_data result;
    result.id = -1;
    result.val = 0.0;
    if (q->size == 0){ return result;}
    result = q->heap[0];
    q->pos_in_heap[result.id] = -1;
    q->size--;
    if (q->size > 0){
        q->heap[0] = q->heap[q->size];
        q->pos_in_heap[q->heap[0].id] = 0;
        sift_down(q, 0);
    }
    return result;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val){
    int pos = q->pos_in_heap[key];
    if (pos == -1){ return;}

    float old_val = q->heap[pos].val;
    q->heap[pos].val = new_val;
   
    if (new_val < old_val){
        sift_up(q, pos);
    }
    else if (new_val > old_val){
        sift_down(q, pos);
    }
}