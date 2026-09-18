#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/circular_buffer_queue.h"


int main(int argc, char* argv[]){

    if (argc < 2){
        printf("Please only provide one interger as input \n");
        return 1;
    }else{
    
        int n = atoi(argv[1]);
        printf("Your input no is: %d \n", n);

        //First initiate an empty queue q of integers,
        struct Queue *q = queue_init(sizeof(int),n);


        //iteratively pick random integers p
        //and then enqueue p in q if p is even
        //and instead dequeue one item from q whenp is odd.
        for(int i = 0; i<n; i++){
            int p = rand() % 101; //generate random between 0 and 100;
            if(p % 2 == 0){
                queue_enqueue(q, &p);
            }else{
                int dest;
                queue_dequeue(q, &dest);

            }
            //the main function should return the largest length l_max
            //of the queue q during the whole process
            printf("Current q length: %d \n",q->length);
        }
    }
    return 0;
}