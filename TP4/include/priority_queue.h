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
}priority_queue;

int priority_queue_init (priority_queue * q );

void priority_queue_push ( priority_queue *q , int id , float val );

priority_data priority_queue_pop (priority_queue * q );

void priority_queue_free(priority_queue *q);

#endif