#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4

void *tfunc(void *args)
{
    int tnum = *((int *) args);
    printf("Hola mundo desde el hilo %d\n",tnum);
    sleep(10);
    printf("Adios mundo desde el hilo %d\n",tnum);
}

int main() 
{
    pthread_t tid[NTHREADS];
    int i;

    for(i=0;i<NTHREADS;i++)
        pthread_create(&tid[i],NULL,tfunc,&i);

    for(i=0;i<NTHREADS;i++)
        pthread_join(tid[i],NULL);
}