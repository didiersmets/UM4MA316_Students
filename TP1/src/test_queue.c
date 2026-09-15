/*Write a file src/test_queue.c that will contain a single main function which is expected
to do the following. First initiate an empty queue q of integers, then iteratively pick
random integers p (through the rand function in the stdlib library) and then enqueue
p in q if p is even and instead dequeue one item (and do nothing with it) from q when
p is odd. The number n of successive random integers to be picked should be given as a
command line argument, and the main function should return the largest length l_max
of the queue q during the whole process.
In order to compile your program, you may use the command:
gcc src/circular_buffer_queue.c src/test_queue.c -I include -o test_queue
We have already encountered the -o (output file) gcc option. The -I option allows to
add some directories to the include path for header files, here the include directory.*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include "../include/circular_buffer_queue.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int cycles;
    int random;
    int *dest;
    int lmax = 0;
    struct Queue *q = queue_init(sizeof(int), 0);

    srand(time(NULL));

    do
    {
        printf("Insert the number of cycles:\n");
        scanf("%d", &cycles);
    } while (cycles < 0);

    for (int i = 0; i < cycles; i++)
    {

        random = rand();
        if (random % 2 == 0)
        {
            queue_enqueue(q, &random);
        }
        else
        {
            queue_dequeue(q, dest);
        }

        lmax = MAX(lmax, queue_length(q));
    }

    printf("The maximum length achieved in the process is: %d\n", lmax);
  
    queue_dispose(q);
   

    return 0;
}
