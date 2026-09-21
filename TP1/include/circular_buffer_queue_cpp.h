#include <cstddef>

template <typename T>
struct Queue
{
    size_t front;
    size_t length;
    size_t capacity;
    T *data;
};


template <typename T>
bool is_empty(const Queue<T> *q)
{
    return q->length == 0;
}


template <typename T>
size_t queue_length(const Queue<T> *q)
{
    return q->length;
}


template <typename T>
Queue<T> *queue_init(size_t capacity)
{
    Queue<T> *q = new Queue<T>;

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->data = new T[capacity];

    return q;
}


template <typename T>
void queue_dispose(Queue<T> *q)
{
    delete[] q->data;
    delete q;
}


template <typename T>
void enlarge_queue_capacity(Queue<T> *q)
{
    size_t old_capacity = q->capacity;
    size_t new_capacity = 2 * old_capacity;

    T *new_data = new T[new_capacity];

    for (size_t i = 0; i < q->length; i++)
    {
        size_t old_index = (q->front + i) % old_capacity;

        new_data[i] = q->data[old_index];
    }

    delete[] q->data;

    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;
}


template <typename T>
void queue_enqueue(Queue<T> *q, const T &value)
{
    if (q->length == q->capacity)
    {
        enlarge_queue_capacity(q);
    }

    size_t index = (q->front + q->length) % q->capacity;

    q->data[index] = value;

    q->length++;
}


template <typename T>
void queue_dequeue(Queue<T> *q, T &value)
{
    if (is_empty(q))
    {
        return;
    }

    value = q->data[q->front];

    q->front = (q->front + 1) % q->capacity;
    q->length--;
}
