#include <stdio.h>
#include <stdlib.h>
#include "../include/circular_buffer_queue.h"


int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("no integer provided in the command line\n");
        return 1;
    }

    size_t elem_size = sizeof(int);
    size_t capacity = 1;

    struct Queue *q = queue_init(elem_size, capacity);

    int n = atoi(argv[1]);
    int p = 0;
    void *tmp;

    while(n>0) {

        p = rand();
        printf("%d\n", p);

        if(p % 2) {
            queue_dequeue(q, tmp);
        }
        else {
            queue_enqueue(q, &p);
        }

        n--;
    }

    return 0;
}