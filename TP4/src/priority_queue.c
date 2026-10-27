#include "priority_queue.h"

#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 16
#define FAILURE (-1)
#define SUCCESS 0

static void swap(priority_queue *q, int pos1, int pos2);
static void sift_up(priority_queue *q, int pos);
static void sift_down(priority_queue *q, int pos);

int priority_queue_init(priority_queue *q, int max_id)
{
    q->heap = malloc(sizeof(priority_data) * INITIAL_CAPACITY);
    if (q->heap == NULL)
    {
        return FAILURE;
    }
    q->pos_in_heap = malloc(sizeof(int) * (max_id + 1));
    if (q->pos_in_heap == NULL)
    {
        free(q->heap);
        return FAILURE;
    }
    for (int i = 0; i <= max_id; i++)
    {
        q->pos_in_heap[i] = -1;
    }
    q->max_id = max_id;
    q->capacity = INITIAL_CAPACITY;
    q->size = 0;
    return SUCCESS;
}

void priority_queue_push(priority_queue *q, int id, float val)
{
    if (id < 0 || id > q->max_id)
    {
        fprintf(stderr, "push: id %d out of range [0, %d]\n", id, q->max_id);
        return;
    }
    if (q->pos_in_heap[id] != -1)
    {
        fprintf(stderr, "push: id %d already in queue (use update)\n", id);
        return;
    }

    if (q->capacity == q->size)
    {
        int new_cap = 2 * q->capacity;
        priority_data *tmp = realloc(q->heap, new_cap * sizeof(priority_data));
        if (tmp == NULL)
        {
            fprintf(stderr, "Failed to push object because no new memory could be reallocated\n");
            return;
        }
        q->heap = tmp;
        q->capacity = new_cap;
    }

    priority_data new_point = {.id = id, .val = val};
    q->heap[q->size] = new_point; // add to end
    q->pos_in_heap[id] = q->size; // record its position
    q->size += 1;                 // new size
    sift_up(q, q->size - 1);      // sift_up
}
priority_data priority_queue_pop(priority_queue *q)
{
    if (q->size == 0)
    {
        return (priority_data){.id = -1, .val = -1};
    }
    priority_data res = q->heap[0];
    q->heap[0] = q->heap[q->size - 1];
    q->pos_in_heap[q->heap[0].id] = 0;   
    q->pos_in_heap[res.id] = -1;         
    q->size--;
    sift_down(q, 0);
    return res;
}

static void swap(priority_queue *q, int pos1, int pos2)
{
    priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;
    q->pos_in_heap[q->heap[pos1].id] = pos1;
    q->pos_in_heap[q->heap[pos2].id] = pos2;
}
static void sift_up(priority_queue *q, int pos)
{
    while (pos > 0)
    {
        int p_pos = (pos - 1) / 2;
        if (q->heap[pos].val >= q->heap[p_pos].val)
            break;
        swap(q, pos, p_pos);
        pos = p_pos;
    }
}
static void sift_down(priority_queue *q, int pos)
{
    while (pos < q->size) // redundant but ok
    {
        int smallest = pos;
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        if (left < q->size && (q->heap[left].val < q->heap[smallest].val))
            smallest = left;
        if (right < q->size && (q->heap[right].val < q->heap[smallest].val))
            smallest = right;
        // we select the smallest child to swap
        if (smallest == pos)
            break;              // nothing to sift down
        swap(q, pos, smallest); // swap
        pos = smallest;
    }
}

void priority_queue_update(priority_queue *q, int key, float new_val)
{
    if (key < 0 || key > q->max_id)
    {
        fprintf(stderr, "update: id %d out of range [0, %d]\n", key, q->max_id);
        return;
    }
    int pos = q->pos_in_heap[key];
    if (pos == -1)
    {
        fprintf(stderr, "update: id %d not in queue\n", key);
        return;
    }

    float old_val = q->heap[pos].val;
    q->heap[pos].val = new_val;

    if (new_val < old_val)
        sift_up(q, pos);
    else if (new_val > old_val)
        sift_down(q, pos);
}

void priority_queue_free(priority_queue *q)
{
    free(q->heap);
    q->heap = NULL;
    q->capacity = q->size = 0;
    free(q->pos_in_heap);
    q->pos_in_heap = NULL;
}