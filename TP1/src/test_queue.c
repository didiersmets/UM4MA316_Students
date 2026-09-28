#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer_queue.h"

int main(int argc, char ** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    struct Queue *q = queue_init(sizeof(int), 10);
    if (q == NULL) {
        return 1;
    }

    size_t l_max = 0;
    int trash;

    for (int i = 0; i < n; i++) {
        int p = rand();
        if (p % 2 == 0) {
            queue_enqueue(q, &p);
        }
        else if (!is_empty(q)) {
            queue_dequeue(q, &trash);
        }

        if (queue_length(q) > l_max) {
            l_max = queue_length(q);
        }
    }

    queue_dispose(q);
    return l_max;
}
