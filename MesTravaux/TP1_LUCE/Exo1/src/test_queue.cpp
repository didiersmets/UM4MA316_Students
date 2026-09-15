#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>


#include "../include/circular_buffer_queue.hpp"

int main(int argc, char *argv[]){
    int N;
    int p;
    int dest;
    argc<2 ? std::cout<<"Veuillez entrer un entier :"<<std::endl, scanf("%d",&N) : (N=atoi(argv[1]));
    srand(time(NULL));

 
    Queue<int> *q = queue_init<int>(0);

    for(int i=0; i<N;i++){
        p=rand()%11;
        printf("p=%d\n",p);
        if (p%2==1){
            queue_enqueue(q,p);
            std::cout<<p<<" entre dans la queue"<<std::endl;
        } else {
            if (!is_empty(q)){
                queue_dequeue(q,&dest);
                std::cout<<dest<<" est sorti de la queue"<<std::endl;
            }
        }
    }

    for(int i=0; i<q->length;i++){
        std::cout<<"position "<<i+1<<" : "<<q->data[(q->front + i)%q->capacity]<<std::endl;
    }
    
    queue_dispose(q);
    return 0;
}