#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>


template <typename T>
struct Queue {
	size_t front; 
	size_t length;
	size_t capacity;
	T *data; 
};


template <typename T>
bool is_empty(Queue<T> *q){
    return q->length==0;
}
template <typename T>
size_t queue_length(Queue<T> *q){
    return q->length;
}

template <typename T>
Queue<T> *queue_init(size_t capacity) {
    Queue<T>* q = new Queue<T>;
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->data = (capacity > 0) ? new T[capacity] : nullptr;
    return q;
}

template <typename T>
void queue_dispose(Queue<T> *q){
    if (!q){
        std::cout<<"erreur queue_dispose : q NULL"<<std::endl;
        exit(1);
    }
    delete[] q->data;
    delete[] q;
}

template <typename T>
void enlarge_queue_capacity (Queue<T> *q){
    if (!q){
        std::cout<<"erreur enlarge : q NULL"<<std::endl;
        exit(1);
    }
    size_t old_cap = q->capacity;
    size_t new_cap = q->capacity == 0 ? 1 : q->capacity*=2;
    T *new_data = new T[new_cap];
    for(int i=0;i<old_cap;i++){
        new_data[i]=q->data[i];
    }
    delete[] q->data;
    q->data = new_data;
    q->capacity = new_cap;
}

template <typename T>
void queue_enqueue(Queue<T> *q, T src){
    if (!q){
        std::cout<<"erreur enqueue : q NULL"<<std::endl;
        exit(1);
    }
    if (q->length>=q->capacity){
        size_t temp = q->capacity;
        enlarge_queue_capacity(q);
        std::cout<<"Enlargement succeeded, capacity goes from "<<temp<<" to "<<q->capacity<<std::endl;
    }
    q->data[(q->front + q->length)%q->capacity]=src;
    q->length++;
}

template <typename T>
void queue_dequeue(Queue<T> *q, T *dest){
    if (!q){
        std::cout<<"erreur dequeue : q NULL"<<std::endl;
        exit(1);
    } 
    if (is_empty(q)) return;
    *dest = q->data[q->front];
    q->length--;
    q->front = (q->front + 1)%q->capacity;
}