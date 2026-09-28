#include <cassert>
#include <cstddef> // for size_t


template <typename T>
struct Queue {
    size_t front;    // index of the first element in the queue
    size_t length;   // number of items presently in the queue
    size_t capacity; // capacity of the queue (in nbr of items)
    T* data;         // address of the array
};

template <typename T>
Queue<T>* queue_init(size_t capacity) {
    Queue<T>* q = new Queue<T>;
    
    q->capacity = capacity;
    q->length = 0;
    q->front = 0;
    
    if (capacity > 0) {
        q->data = new T[capacity]; 
    } else {
        q->data = nullptr; 
    }
    
    return q;
}

template <typename T>
bool is_empty(const Queue<T>* q) {
    return q->length == 0;
}

template <typename T>
size_t queue_length(const Queue<T>* q) {
    return q->length;
}

template <typename T>
void queue_dispose(Queue<T>* q) {
    if (q == nullptr) {
        return;
    }
    delete[] q->data; // C++ array deallocation
    delete q;         // C++ object deallocation
}

template <typename T>
void enlarge_queue_capacity(Queue<T>* q) {
    if (q->length < q->capacity) {
        return;
    }
    size_t new_cap = q->capacity == 0 ? 1 : 2 * q->capacity;
    

    T* new_memory = new T[new_cap];

    
    for (size_t i = 0; i < q->length; i++) {
        size_t circular_idx = (q->front + i) % q->capacity;
        new_memory[i] = q->data[circular_idx]; 
    }

    delete[] q->data;
    q->data = new_memory;
    q->capacity = new_cap;
    q->front = 0;
}

template <typename T>
void queue_enqueue(Queue<T>* q, const T& src) {
    assert(q != nullptr);
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }
    
    size_t tail_queue_index = (q->front + q->length) % q->capacity;
    q->data[tail_queue_index] = src; 
    q->length++;
}

template <typename T>
void queue_dequeue(Queue<T>* q, T* dest) {
    assert(q != nullptr);
    assert(dest != nullptr);
    if (is_empty(q)) {
        return;
    }
    
    *dest = q->data[q->front]; 
    q->front = (q->front + 1) % q->capacity;
    q->length--;
}