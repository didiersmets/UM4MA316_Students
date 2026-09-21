#include "../include/circular_buffer_queue_cpp.h"

#include <cstdlib>
#include <iostream>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please give n" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);

    Queue<int> *q = queue_init<int>(10);

    size_t l_max = 0;

    for (int i = 0; i < n; i++)
    {
        int p = std::rand();

        if (p % 2 == 0)
        {
            queue_enqueue(q, p);
        }
        else
        {
            if (!is_empty(q))
            {
                int x;
                queue_dequeue(q, x);
            }
        }

        if (queue_length(q) > l_max)
        {
            l_max = queue_length(q);
        }
    }

    std::cout << l_max << std::endl;

    queue_dispose(q);

    return (int)l_max;
}
