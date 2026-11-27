#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int priority_queue_init(struct priority_queue *q) {
    q-> capacity = 4;
    q-> size =0;
    q->heap = malloc( q->capacity * sizeof(struct priority_data));
    if (q->heap == NULL) {
        return -1;
    }
    return 0;

}


static void swap(struct priority_queue *q, int pos1, int pos2) {
    struct priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;
}

static void sift_up(struct priority_queue *q, int pos) {   
    while (pos >0 && q->heap[(pos -1)/2].val > q->heap[pos].val) {
        int parent = (pos -1)/2;
        swap (q, parent, pos);
        pos = parent;
    }
}

static void sift_down(struct priority_queue *q, int pos) {
    while (2*pos + 1 < q->size) {
        int child = 2*pos +1; 
        if (child + 1 < q->size && q->heap[child+1].val < q->heap[child].val) {
            child = child + 1;
        }
        if (q->heap[pos].val <= q->heap[child].val)
            break;
        swap (q, child, pos);
        pos = child;
    }
}

void priority_queue_push(struct priority_queue *q, int id, float val) {
    if (q->size == q->capacity) {  
        q->capacity *= 2;
        q->heap = realloc(q->heap, q->capacity * sizeof(struct priority_data));
    }
    q->heap[q->size].id = id;        
    q->heap[q->size].val = val;
    sift_up(q, q->size);               
    q->size++;                            
}


struct priority_data priority_queue_pop(struct priority_queue *q) {
    struct priority_data top = q->heap[0];
    q->size--;
    q->heap[0] = q->heap[q->size];
    sift_down(q, 0);
    return top;
}