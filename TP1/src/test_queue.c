#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"

#define INITIAL_CAPACITY 1

int main(int argc, char *argv[]){

    if (argc < 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    srand(time(NULL));

    // Start small so that enlarge_queue_capacity is actually exercised
    struct Queue * q = queue_init(sizeof(int), INITIAL_CAPACITY);
    if (q == NULL) {
        return 1;
    }
    size_t max_len = 0;

    for(int i = 0; i<n; i++){
        int p = rand();
        if(p%2==0){
            queue_enqueue(q, &p);
            if(max_len<queue_length(q)){
                max_len = queue_length(q);
            }
        }else if(!is_empty(q)){
            int waste;
            queue_dequeue(q, &waste);
        }
    }

    queue_dispose(q);

    printf("Max length = %zu\n", max_len);

    return 0;
}
