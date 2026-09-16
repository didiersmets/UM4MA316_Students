#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/circular_buffer_queue.h"

int main(int argc, char *argv[]){

    if (argc < 2) { return 1; }

    int n = atoi(argv[1]);

    struct Queue * q = queue_init(sizeof(int),n);
    size_t max_len = 0;

    for(int i = 0; i<n; i++){
        int p = rand();
        if(p%2==0){
            queue_enqueue(q, &p);
            if(max_len<queue_length(q)){
                max_len = queue_length(q);
            }
        }else{
            int waste;
            queue_dequeue(q, &waste);
        }
    }

    printf("Max length = %zu\n", max_len);

    return 0;
}