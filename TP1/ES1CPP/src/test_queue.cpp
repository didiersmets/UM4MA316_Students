#include <cstdlib> 
#include <iostream>
#include "../include/circular_buffer_queue.h"

int main(int argc, char *argv[]){

    if (argc < 2) { return 1; }

    int n = atoi(argv[1]);

    Queue<int> * q = queue_init<int>(n);
    size_t max_len = 0;

    for(int i = 0; i<n; i++){
        int p = rand();
        if(p%2==0){
            queue_enqueue(q, p);
            if(max_len<queue_length(q)){
                max_len = queue_length(q);
            }
        }else{
            int waste;
            queue_dequeue(q, &waste);
        }
    }

    queue_dispose(q);

    std::cout << "Max length = " << max_len << "\n";

    return 0;
}