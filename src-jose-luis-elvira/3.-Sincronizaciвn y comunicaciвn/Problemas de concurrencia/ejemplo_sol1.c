#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4
#define ITERS 1000000000

long long g=0;
int arrres[NTHREADS];

void *tfunc(void *args)
{
    int nthread = *((int *) args);
	int i;
    int lg=0;

	arrres[nthread] = 0;

	for(i=0;i<ITERS;i++)
		lg++;
		//arrres[nthread]++;

    arrres[nthread] = lg;
}

int main()
{
	pthread_t tid[NTHREADS];
    int argarr[NTHREADS];
	int i;
	
	for(i=0;i<NTHREADS;i++)
	{
        argarr[i] = i;
		pthread_create(&tid[i],NULL,tfunc,&argarr[i]);
		// usleep(100000);
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);

	for(i=0;i<NTHREADS;i++)
        g += arrres[i];
	printf("g=%lld\n",g);
}