#include "../include/prio_queue.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int priority_queue_init(struct priority_queue *q, int max_id) {

  q->capacity = 4; /* minimal power of 2 to get a root and two children */
  q->size = 0;
  q->heap = malloc(4 * sizeof(struct priority_data));

  if (q->heap == NULL) {
    return 0;
  }

  q->pos_in_heap = malloc((max_id+1) * sizeof(int));

  if (q->pos_in_heap == NULL) {
    free(q->heap);
    return 0;
  }

  for (int i=0; i<max_id+1; i++) {
    q->pos_in_heap[i] = -1;
  }

  return 1;
}

// added this for test 

void priority_queue_fini(struct priority_queue *q) {

  free(q->heap);
  free(q->pos_in_heap);
}

static void swap(struct priority_queue *q, int pos1, int pos2) {

  struct priority_data tmp = q->heap[pos1];
  q->heap[pos1] = q->heap[pos2];
  q->heap[pos2] = tmp;
  
  q->pos_in_heap[q->heap[pos1].id] = pos1;
  q->pos_in_heap[q->heap[pos2].id] = pos2;
}

// we're using a max on top binary heap

static void sift_up(struct priority_queue *q, int pos) {

  int i = pos;

  while ((i != 0) && (q->heap[i].val > q->heap[(i-1)/2].val)) {
    
    swap(q, i, (i-1)/2);
    i = (i-1)/2;
  }
}

static void sift_down(struct priority_queue *q, int pos) {

  int i = pos;
  
  while(true) {
    
    if (2*i+1 > q->size) {
      break;
    }

    else if ((q->size == 2*i+1) && (q->heap[i].val < q->heap[2*i+1].val)) {  
      swap(q, i, 2*i+1);
      break;
    }

    else if (q->size >= 2*i+2) {

      int larger = (q->heap[2*i+1].val > q->heap[2*i+2].val) ? 2*i+1 : 2*i+2;

      if (q->heap[i].val < q->heap[larger].val) {
        swap(q, i, larger);
        i = larger;
      } 

      else {
        break;
      }
    }
  }
}

void priority_queue_push(struct priority_queue *q, int id, float val) {

  if (q->pos_in_heap[id] != -1) {
    fprintf(stderr, "id %d already assigned\n", id);
    exit(EXIT_FAILURE);
  }

  if (q->size == q->capacity) {

    int new_cap = 2 * q->capacity;
    struct priority_data *new_heap = realloc(q->heap, new_cap * sizeof(struct priority_data));

    if (new_heap == NULL) {
      fprintf(stderr, "Allocation failed\n");
      exit(EXIT_FAILURE);
    }

    q->heap = new_heap;
    q->capacity = new_cap;
  }
  
  q->heap[q->size].id = id;
  q->heap[q->size].val = val;
  q->pos_in_heap[id] = q->size;
  sift_up(q, q->size);

  q->size++;
}

struct priority_data priority_queue_pop(struct priority_queue *q) {
  
  if (q->size == 0) {
    fprintf(stderr, "Empty priority_queue\n");
    exit(EXIT_FAILURE);
  }

  struct priority_data res = q->heap[0];
  q->pos_in_heap[res.id] = -1;

  q->heap[0] = q->heap[--q->size];
  q->pos_in_heap[q->heap[0].id] = 0;

  sift_down(q, 0);

  return res;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val) {

  int pos = q->pos_in_heap[key];

  if (pos == -1) {
    fprintf(stderr, "id %d is not in the heap\n", key);
    exit(EXIT_FAILURE);
  }

  float old_val = q->heap[pos].val;
  q->heap[pos].val = new_val;

  if (q->heap[pos].val < old_val) {
    sift_down(q, pos);
  }
  
  else if (q->heap[pos].val > old_val) {
    sift_up(q, pos);
  }
}
