#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define NTHREADS 4

#define TAM 2000

double a[TAM][TAM], b[TAM][TAM], c[TAM][TAM];

void *tfunc(void *args) 
{
    int tnum = *((int *) args);
    int inicio = tnum * (TAM/NTHREADS);
    int fin = inicio + (TAM/NTHREADS);
    int i,j,k;

    printf("Hilo %d, desde %d hasta %d\n",tnum,inicio,fin-1);

    for(i=inicio;i<fin;i++)
        for(k=0;k<TAM;k++)
            for(j=0;j<TAM;j++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];

}

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

    pthread_t tid[NTHREADS];
    int targs[NTHREADS];

    int i;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    for(i=0;i<NTHREADS;i++)
    {
        targs[i] = i;
        pthread_create(&tid[i],NULL,tfunc,&targs[i]);
    }

    for(i=0;i<NTHREADS;i++)
        pthread_join(tid[i],NULL);


    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}