#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4
#define ITERS 10000

int g=0;

void *tfunc(void *args)
{
	int i;
	for(i=0;i<ITERS;i++)
		g++;
}

int main()
{
	pthread_t tid[NTHREADS];
	int i;
	
	for(i=0;i<NTHREADS;i++)
	{
		pthread_create(&tid[i],NULL,tfunc,NULL);
		// usleep(100000);
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);
	
	printf("g=%d\n",g);
}