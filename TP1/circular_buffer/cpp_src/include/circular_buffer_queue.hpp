#include <cstddef> // for size_t
#include <iostream>

template <typename T>
struct Queue {
	size_t front; // index of the first element in the queue
	size_t length; // number of items presently in the queue
	size_t capacity; // capacity of the queue (in nbr of items)
	T *data; // address of the array
};

template <typename T>
bool is_empty(const struct Queue<T> *q);

template <typename T>
size_t queue_length(const struct Queue<T> *q);

template <typename T>
struct Queue<T> *queue_init(size_t capacity);

template <typename T>
void queue_dispose(struct Queue<T> *q);

template <typename T>
void queue_enqueue(struct Queue<T> *q, const T *src);

template <typename T>
void queue_dequeue(struct Queue<T> *q, T *dest);

template <typename T>
static void enlarge_queue_capacity(struct Queue<T> * q);



template <typename T>
bool is_empty(const struct Queue<T> *q){
	return q->length == 0;
}

template <typename T>
size_t queue_length(const struct Queue<T> *q){
	return q->length;
}

template <typename T>
struct Queue<T> *queue_init(size_t capacity){
	//declare the new queue with new instead of malloc
	Queue<T> *q = new Queue<T>;
	T *data = new T[capacity];

	q->data = data; 

	q->front = 0;
    q->length = 0;
    q->capacity = capacity;

	return q;
}

template <typename T>
void queue_dispose(struct Queue<T> *q){
	delete[] q->data;
	delete q;
}

template <typename T>
void queue_enqueue(struct Queue<T> *q, const T *src){
	if(q->length == q->capacity){
        enlarge_queue_capacity(q);
    }

	size_t index = (q->front + q->length) % q->capacity;
	q->data[index] = *src;

    q->length++;
}

template <typename T>
void queue_dequeue(struct Queue<T> *q, T *dest){
	if(q->length == 0){ //the queue is already empty
        std::cout << "Dequeue was called althought the queue is empty \n";
    }else{
		*dest = q->data[q->front];

		q->length--;

		q->front++;
		if (q->front == q->capacity){
            q->front = 0;
        }
	}
}

template <typename T>
static void enlarge_queue_capacity(struct Queue<T> * q){

	size_t new_capacity = q->capacity * 2;

	T* new_data = new T[new_capacity];

	for(int e = 0; e<q->length; e++){
		size_t index_q = (q->front + e) % q->capacity;
		size_t index_new_q = e;

		new_data[index_new_q] = q->data[index_q];
	}
	delete[] q->data;
	q->data = new_data;
	
	q->front = 0;
    q->capacity = new_capacity;

}