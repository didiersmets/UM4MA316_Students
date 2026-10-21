#include "standard_heap_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {


    struct Priority_queue *pq = malloc(sizeof(struct Priority_queue));
    if(priority_queue_init(pq, 1)) {
        printf("error initializing the priority queue\n");
        free(pq);
        return 1;
    }

    priority_queue_push(pq, 2, 18);
    priority_queue_push(pq, 2, 11);
    priority_queue_push(pq, 2, 6);
    priority_queue_push(pq, 2, 7);
    priority_queue_push(pq, 2, 6);
    priority_queue_push(pq, 2, 3);
    priority_queue_push(pq, 2, 4);
    priority_queue_push(pq, 2, 5);
    priority_queue_push(pq, 2, 1);
    priority_queue_push(pq, 2, 2);
    priority_queue_push(pq, 2, 4);
    priority_queue_push(pq, 2, 1);
    priority_queue_push(pq, 2, 10);

    printf("popped value: %.17g\n", priority_queue_pop(pq).val);
    
    for(int i = 0; i < pq -> size; i++) {
        printf("%d element in the queue has value %.17g\n", i, pq -> heap[i].val);
    }



    return 0;
}