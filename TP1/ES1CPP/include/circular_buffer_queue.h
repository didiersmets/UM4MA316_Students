#include <cstddef> 
#include <iostream>

template <typename T>
struct Queue {
    size_t front;
    size_t length;
    size_t capacity;
    T *data;
};

template <typename T>
bool is_empty(const Queue<T> *q);

template <typename T>
size_t queue_length(const Queue<T> *q);

template <typename T>
Queue<T> *queue_init(size_t capacity);

template <typename T>
void queue_dispose(Queue<T> *q);

template <typename T>
void queue_enqueue(Queue<T> *q, const T src); 

template <typename T>
void queue_dequeue(Queue<T> *q, T *dest);



template <typename T>
void enlarge_queue_capacity ( Queue<T> * q ){
    size_t new_capacity = (q->capacity == 0) ? 1 : (q->capacity * 2);
    T* new_data = new T[new_capacity]; 

    for(size_t i = 0; i < q->length; i++){
        size_t old_idx = (q->front + i) % q->capacity;
        new_data[i] = q->data[old_idx];
    }

    delete[] q->data;

    q->data = new_data;
    q->capacity = new_capacity;

    q->front = 0;
}

template <typename T>
bool is_empty(const Queue<T> *q){
    return q->length == 0;
}

template <typename T>
size_t queue_length(const Queue<T> *q){
    return q->length;
}

template <typename T>
Queue<T> * queue_init (size_t capacity ){
    Queue<T>* q = new Queue<T>;
    q->data = new T[capacity];
    q -> front = 0;
    q -> length = 0;
    q -> capacity = capacity;
    return q;
}

template <typename T>
void queue_dispose(Queue<T> *q){
    if(q!=nullptr){
        if(q->data!=nullptr){
            delete[] q->data;
        }
        delete q;
    }    
}

template <typename T>
void queue_enqueue (Queue<T> *q , const T src ){
    if(q -> capacity == q -> length){
        std::cout << "Capacity full! Enlarging the queue.";
        enlarge_queue_capacity(q);
    }

    size_t idx = (q -> front + q -> length) % q -> capacity;

    q->data[idx] = src;

    q -> length ++;
}

template <typename T>
void queue_dequeue(Queue<T> *q, T *dest) {
    if (q->length == 0) {
        std::cout << "Error, queue empty\n";
        return;
    }

    *dest = q->data[q->front];
            
    q->front = (q->front + 1) % q->capacity; 
    q->length -= 1;
}