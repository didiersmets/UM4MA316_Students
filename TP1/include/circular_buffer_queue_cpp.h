#include <cstddef>

template <typename T>
struct Queue {
    size_t front;
    size_t length;
    size_t capacity;
    T *data;
};

template <typename T>
static void enlarge_queue_capacity(Queue<T> *q);

template <typename T>
Queue<T> *queue_init(size_t capacity){
    Queue<T> *queue = new Queue<T>;
    queue -> front = 0; // index of the first element in the queue
	queue -> length = 0; // number of items presently in the queue
	queue -> capacity = capacity; // capacity of the queue (in nbr of items)
	queue -> data = new T[capacity]; // address of the array
    return queue;
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
void queue_dispose(Queue<T> *q){
    if (q == nullptr) return;
    delete[] q->data;
    delete q;
}

template <typename T>
void queue_enqueue(Queue<T> *q, const T src){
    if (q->length == q->capacity){
        enlarge_queue_capacity(q);
    }
    size_t tail = (q->front + q->length) % q->capacity;
    q->data[tail] = src;
    q->length++;
}

template <typename T>
void queue_dequeue(Queue<T> *q, T &dest){
    if (q->length == 0) return;
    dest = q->data[q->front];
    q->front =(q->front + 1) % q->capacity;
    q->length--;
}

template <typename T>
static void enlarge_queue_capacity(Queue<T> *q){
    size_t newcapacity = q->capacity + 1;
    T *newdata = new T[newcapacity];

    for (size_t i = 0; i < q->length; i++) {
        size_t old_index = (q->front + i) % q->capacity;
        newdata[i] = q -> data[old_index];
    }
    delete[] q->data;
    q->data = newdata;
    q->capacity = newcapacity;
    q->front = 0;
}