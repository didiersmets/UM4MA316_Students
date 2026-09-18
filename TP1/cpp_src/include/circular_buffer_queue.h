#include <stdbool.h>
#include <stddef.h> // for size_t

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

