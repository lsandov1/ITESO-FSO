#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *tfunc(void *args)
{
    printf("Hola mundo\n");
    sleep(10);
    printf("Adios mundo\n");
}

int main() 
{
    pthread_t tid;

    pthread_create(&tid,NULL,tfunc,NULL);

    pthread_join(tid,NULL);
}