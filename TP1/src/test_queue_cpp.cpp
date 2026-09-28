#include "circular_buffer_queue_cpp.h"
#include<cstdlib>

int main(int argc, char *argv[])
{
	if(argc!=2)
		return EXIT_FAILURE;
	int n=std::atoi(argv[1]);
	if(n<0)
		return EXIT_FAILURE;
	Queue<int> *q = queue_init<int>(1);
	size_t l_max =0;
	for (int i=0; i<n; ++i)
	{
		int p=std::rand();
		if(p%2==0)
		{
			queue_enqueue(q,p);
		}
		else
		{
			if(!is_empty(q)){
				int value;
				queue_dequeue(q,value);}}
		if(queue_length(q)>l_max)
			l_max=queue_length(q);
	}
	queue_dispose(q);
	return static_cast<int>(l_max);
}