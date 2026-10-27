#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int main(void)
{
    priority_queue q;
    priority_queue_init(&q, 99);

    for (int i = 0; i < 100; i++)
        priority_queue_push(&q, i, (float)(rand() % 1000));

    priority_queue_update(&q, 42, -1.0f);
    priority_data d = priority_queue_pop(&q);
    printf("first pop: id %d (expected 42), pos_in_heap[42] = %d (expected -1)\n",
           d.id, q.pos_in_heap[42]);

    priority_queue_update(&q, 7, 5000.0f);

    float prev = -1.0f;
    int errors = 0, count = 0;
    while (q.size > 0)
    {
        d = priority_queue_pop(&q);
        if (d.val < prev)
            errors++;
        prev = d.val;
        count++;
    }
    printf("last pop: id %d (expected 7)\n", d.id);
    printf("popped %d (expected 99), %d ordering errors\n", count, errors);

    priority_queue_free(&q);
    return 0;
}