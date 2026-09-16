#include <iostream>
#include <cstdlib>
#include <ctime>
#include "circular_buffer_queue_cpp.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        return 1;
    }

    Queue<int> *q = queue_init<int>(0);
    size_t l_max = 0;
    srand(time(NULL));
    
    for (int i = 0; i < std::atoi(argv[1]); i++){
        int n = std::rand();

        if (n%2 == 0){
            queue_enqueue<int>(q, n);
        } else {
            int trash = 1;
            queue_dequeue<int>(q, trash);
        }
        if (q->length > l_max){l_max = q->length;}
    }
   
    queue_dispose(q);
    std::cout << l_max << std::endl;
    return 0;

}