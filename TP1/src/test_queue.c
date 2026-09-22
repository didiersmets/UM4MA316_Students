#include<stdio.h>
#include<stdlib.h>
#include "../include/circular_buffer_queue.h"

int main(int argc, char** argv){
    int n = atoi(argv[1]);
    struct Queue * q = queue_init(sizeof(int), 10);
    int l_max = 0;
    for (int i = 0; i<n;i++){
        int p = rand()%101;
        
        if (p % 2 == 0){
            queue_enqueue(q,&p);
            l_max ++ ;
        }else{
            queue_dequeue(q,&p);
        }
      if (q->length >= l_max){
            l_max = q->length;
        }
    }
    free(q->data);
    free(q);
    printf("%d\n",l_max);
}
    
