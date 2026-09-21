#include "../include/circular_buffer_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);

    struct Queue *q = queue_init(sizeof(int), 10);

    size_t l_max = 0;

    for (int i = 0; i < n; i++)
    {
        int p = rand();

        if (p % 2 == 0)
        {
            queue_enqueue(q, &p);
        }
        else
        {
            if (!is_empty(q))
            {
                int x;
                queue_dequeue(q, &x);
            }
        }

        if (queue_length(q) > l_max)
        {
            l_max = queue_length(q);
        }
    }

    printf("%zu\n", l_max);

    queue_dispose(q);

    return 0;
}
