#include <stdio.h>
#include <stdlib.h>
#include "../include/circular_buffer_queue.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "%s <integer> <number of random integers to pick>", argv[0]);
        return 1;
    }

    char *endptr;
    int q = strtol(argv[1], &endptr, 10);
    int n = strtol(argv[2], &endptr, 10);

    struct Queue *my_queue = queue_init(sizeof(int), q);
    puts("Queue initialized.");


    printf("Is the queue empty ?\n%d\n", is_empty(my_queue));
    int p;
    for (size_t i = 0 ; i < n ; i++) {
        p = rand();
        printf("Picked %d\n", p);
        if (p%2 == 0) {
            queue_enqueue(my_queue, &p);
        }
        else {
            queue_dequeue(my_queue, &p);

        }
    }
    

    while (!(is_empty(my_queue))) {
        printf("Emptying the queue...\n");
        queue_dequeue(my_queue, &p);
        printf("Dequeued %d\n", p);
    }

    puts("Queue emptied successfully!");

    
    return 0;
}