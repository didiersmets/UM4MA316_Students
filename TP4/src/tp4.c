#include "standard_heap_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {


    struct Priority_queue *pq = malloc(sizeof(struct Priority_queue));
    if(priority_queue_init(pq, 12)) {
        printf("error initializing the priority queue\n");
        free(pq);
        return 1;
    }

    priority_queue_push(pq, 0, 18);
    priority_queue_push(pq, 1, 11);
    priority_queue_push(pq, 2, 6);
    priority_queue_push(pq, 3, 7);
    priority_queue_push(pq, 4, 6);
    priority_queue_push(pq, 5, 3);
    priority_queue_push(pq, 6, 4);
    priority_queue_push(pq, 7, 5);
    priority_queue_push(pq, 8, 1);
    priority_queue_push(pq, 9, 2);
    priority_queue_push(pq, 10, 4);
    priority_queue_push(pq, 11, 1);
    priority_queue_push(pq, 12, 10);

    printf("popped value: %.17g\n", priority_queue_pop(pq).val);
    
    for(int i = 0; i < pq -> size; i++) {
        printf("%d element in the queue has value %.17g\n", i, pq -> heap[i].val);
    }

    // for(int i = 0; i < 13; i++) {
    //     printf("position in heap of the data with id %d: %d\n", i, pq -> pos_in_heap[i]);
    // }

    priority_queue_update(pq, 10, 15);
    printf("after update: \n");
    for(int i = 0; i < pq -> size; i++) {
        printf("%d element in the queue has value %.17g\n", i, pq -> heap[i].val);
    }

    for(int i = 0; i < 13; i++) {
        printf("position in heap of the data with id %d: %d\n", i, pq -> pos_in_heap[i]);
    }

    return 0;
}