#include <stdbool.h>
#include <stddef.h> // for size_t
#include <stdlib.h>
#include <stdio.h>

// Public functions

template <typename T>
struct Queue
{
private:
    size_t front;    // index of the first element in the queue
    size_t length;   // number of items presently in the queue
    size_t capacity; // capacity of the queue (in nbr of items)
    T *data;         // address of the array

    bool is_full () const
    {
        return length == capacity;
    }

    void enlarge_queue_capacity()
    {
        size_t new_capacity, old_index;
        T *new_data;

        new_capacity = capacity == 0 ? 8 : capacity * 2;

        new_data = static_cast<T *>(malloc(new_capacity * sizeof(T)));
        if (!new_data)
        {
            printf("Error allocating memory\n");
            return;
        }

        for (size_t i = 0; i < length; ++i)
        {
            old_index = (front + i) % capacity;
            new_data[i] = data[old_index];
        }

        free(data);
        data = new_data;
        capacity = new_capacity;
        front = 0;
    }

public:
    bool is_empty() const
    {
        return length == 0;
    }

    size_t queue_length() const
    {
        return length;
    }

    Queue(size_t cap) : front(0), length(0), capacity(cap)
    {
        if (capacity > 0)
        {
            data = static_cast<T *>(malloc(capacity * sizeof(T)));
        }
        else
        {
            data = nullptr;
        }
    }

    ~Queue()
    {
        free(data);
        data = nullptr;
        length = 0;
        capacity = 0;
    }

    void queue_enqueue(const T &src)
    {
        size_t tail;

        if (is_full())
        {
            enlarge_queue_capacity();
        }

        tail = (front + length) % capacity;
        data[tail] = src;

        length++;
    }

    void queue_dequeue(T &dest)
    {
        if (is_empty())
        {
            return;
        }

        dest = data[front];

        front = (front + 1) % capacity;
        length--;

        return;
    }
};
