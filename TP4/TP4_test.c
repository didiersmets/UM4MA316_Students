#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int main(void)
{
    priority_queue q;
    if (priority_queue_init(&q) != 0) {
        fprintf(stderr, "init failed\n");
        return 1;
    }

    int n = 100;
    for (int i = 0; i < n; i++)
        priority_queue_push(&q, i, (float)(rand() % 1000));

    float prev = -1;
    int count = 0, errors = 0;
    while (q.size > 0) {
        priority_data d = priority_queue_pop(&q);
        if (d.val < prev) errors++;
        prev = d.val;
        count++;
    }

    printf("popped %d/%d, %d ordering errors\n", count, n, errors);
    priority_queue_free(&q);
    return errors != 0 || count != n;
}