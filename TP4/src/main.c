#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../include/prio_queue.h"

#define MAX_ID 16

int main(){

  srand(time(NULL));

  struct priority_queue q;
  if (priority_queue_init(&q, MAX_ID)) {

    for (int i=0; i<MAX_ID; i++) {
      
      float r = rand() % 100 + 1;
      priority_queue_push(&q, i, r);
    }

    struct priority_data node = priority_queue_pop(&q);
    printf("Largest node is %f of id %d\n", node.val, node.id);

    priority_queue_update(&q, (node.id+1) % MAX_ID, 200.);
    struct priority_data new_node = priority_queue_pop(&q);
    printf("New max priority node %f of id %d\n", new_node.val, new_node.id);
  }
  
  return 0;
}
