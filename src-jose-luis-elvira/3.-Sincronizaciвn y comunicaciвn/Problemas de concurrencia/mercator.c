/*
       This simple code demonstrates CreateEvent, WaitForMultipleObjects
       This code computes sum of Mercator's series.

       Mercator's series expression for ln( x + 1 ) function is:
             ln( x + 1 ) = x - x^2/2 + x^3/3 - x^4/4 + x^5/5 - ...
             for -1 < x <= 1.
			 
		Para compilar incluir las librerías pthread y m (matemáticas)
		
		gcc -o mercator mercator.c -lpthread -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define NUMTHREADS 4
#define SERIES_MEMBER_COUNT 20000

pthread_t *threadHandles, masterThreadHandle;

pthread_mutex_t countCS;

double *sums;
double x = 1.0, res = 0.0;
int threadCount = 0;
int startall = 0;

double getMember(int n, double x)
{
	double numerator = 1;

	for( int i=0; i<n; i++ )
		numerator = numerator*x;

	if ( n % 2 == 0 )
		return ( - numerator / n );
	else
		return numerator/n;
}

void *threadProc(void *par)	// Slave threads
{
	int threadIndex = *((int *)par);

	while(!startall);	// Busy waiting, wasting CPU time
	sums[threadIndex] = 0;
	for(int i=threadIndex; i<SERIES_MEMBER_COUNT;i+=NUMTHREADS)
		sums[threadIndex] += getMember(i+1, x);

    //Signal Master thread that one more processing thread is done
	pthread_mutex_lock(&countCS);
	  threadCount++;
	pthread_mutex_unlock(&countCS);

	free(par);
	return 0;
}

void *masterThreadProc(void *par)
{
	sleep(1);
	startall=1;

	while (threadCount != NUMTHREADS) {}   // busy wait until all threads are done with computation of partial sums

	res = 0;
	for(int i=0; i<NUMTHREADS; i++)
		res += sums[i];
	return 0;
}

int main()
{
	int *threadIdPtr;
	
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	
	threadHandles = malloc(sizeof(pthread_t) * (NUMTHREADS + 1));
	pthread_mutex_init(&countCS,NULL);
	sums = malloc(sizeof(double) * NUMTHREADS);
 
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	for(int i=0; i<NUMTHREADS;i++)
	{
		threadIdPtr = malloc(sizeof(int));
		*threadIdPtr = i;
		pthread_create(&threadHandles[i],NULL,threadProc,threadIdPtr);
	}

	pthread_create(&threadHandles[NUMTHREADS],NULL,masterThreadProc, NULL);
	printf("Count of ln(1 + x) Mercator's series members is %d\n",SERIES_MEMBER_COUNT);
	printf("Argument value of x is %f\n", (double)x);

	for(int i=0;i<NUMTHREADS+1;i++)
		pthread_join(threadHandles[i],NULL);
       
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;
	
	printf("Tiempo = %lld segundos\n", elapsed_time);
	
	free(threadHandles);
	pthread_mutex_destroy(&countCS);
	free(sums);

	printf("Result is %10.8f\n", res);
	printf("By function call ln(1 + %f) = %10.8f\n",x, log(1+x));
}