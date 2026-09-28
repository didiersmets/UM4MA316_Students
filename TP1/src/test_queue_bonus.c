#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<process.h>
#include"circular_buffer_queue.h"
int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Please entre the parameter correctly.\n");
		return 0;
	}
	int n=atoi(argv[1]);
	struct Queue *q=queue_init(sizeof(int), n);
	if(n==0){
		return 0;
	}
	int l_max=0;
	srand((unsigned)time(NULL)^(unsigned)_getpid());
	for(int i=0; i<n; i++){
		int p=rand();
		if(p%2==0){
			queue_enqueue(q, &p);
		}else{
			if(q->length!=0){
				int dummy;
				queue_dequeue(q,&dummy);
			}
		}
		if(l_max<q->length){
			l_max=q->length;
		}
	}
	printf("%zu\n",l_max);
	return (int)l_max;
}
