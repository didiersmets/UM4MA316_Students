#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer_queue.h"

int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);
	struct Queue*q = queue_init(sizeof(int), 10);

	if (q==NULL) {
		printf("Erreur : queue non créée\n");
		return 1;
	}

	int p;
	int l_max = 0;
	for (int i=0; i<n; i++) 
	{
		p = rand();

		if (p%2 == 0) {
			queue_enqueue(q, &p);
		} else {
			if (q->length > 0) {
				int dummy;
			        queue_dequeue(q, &dummy);
			}
		}

		if (l_max < q->length) {
			l_max = q->length;
		}
	}

	free(q->data);
	free(q);
	printf("%d\n", l_max);

}


