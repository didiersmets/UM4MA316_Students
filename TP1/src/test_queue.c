#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "circular_buffer_queue.h"

int main(int argc, char *argv[]) {

    struct Queue *q = queue_init(sizeof(int), 0);
    int l_max = 0;   
    srand(time(NULL)); 

    if (argc < 2) {
        return 1;
    }
    
    for (int i = 0; i < atoi(argv[1]); i++){
        int n = rand();

        if (n%2 == 0){
            queue_enqueue(q, &n);
        } else {
            int trash;
            queue_dequeue(q, &trash);
        }
        if (q->length > l_max){l_max = q->length;}
    }
   
    queue_dispose(q);
    printf("%d \n", l_max);
    return 0;

}