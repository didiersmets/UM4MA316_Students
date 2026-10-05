#include <stdbool.h>
#include <stddef.h> // for size_t

struct Queue;

bool is_empty(const struct Queue *q);

size_t queue_length(const struct Queue *q);

struct Queue *queue_init(size_t elem_size, size_t capacity);

void queue_dispose(struct Queue *q);

void queue_enqueue(struct Queue *q, const void *src);

void queue_dequeue(struct Queue *q, void *dest);

