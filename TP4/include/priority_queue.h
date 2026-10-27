#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct
{
    int id;
    float val;
}priority_data;

typedef struct
{
    priority_data* heap;
    int capacity;
    int size;
    int max_id;
    int * pos_in_heap ;
}priority_queue;

int priority_queue_init (priority_queue * q, int max_id);

void priority_queue_push ( priority_queue *q , int id , float val );

priority_data priority_queue_pop (priority_queue * q );

void priority_queue_update(priority_queue *q , int key , float new_val);

void priority_queue_free(priority_queue *q);



#endif