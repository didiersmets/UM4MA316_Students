#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer_queue.h"
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    srand(0);
    struct Queue q;
    queue_init(&q, sizeof(int));
    size_t l_max = 0;
    for (int i = 0; i < n; ++i) {
        int p = rand();
        if (p % 2 == 0) {
            queue_enqueue(&q, &p);
        } else {
            if (!queue_is_empty(&q)) {
                int dummy;
                queue_dequeue(&q, &dummy);
            }
        }
        size_t len = queue_length(&q);
        if (len > l_max) l_max = len;
    }
    printf("l_max = %zu\n", l_max);
    queue_free(&q);
    return (int)l_max;
}