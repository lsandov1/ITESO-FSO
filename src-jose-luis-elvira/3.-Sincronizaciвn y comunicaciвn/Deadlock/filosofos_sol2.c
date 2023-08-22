#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "semaphoresarr.h"

#define FILOSOFOS 5
#define HABITACION FILOSOFOS

int semaforo;

void filosofo(int i) 
{
    int tenedor_i = i;
    int tenedor_d = (i + 1) % FILOSOFOS;
    int n = 10;

    while(n--)
    {
        semwait(semaforo,HABITACION);

        semwait(semaforo,tenedor_i);
        usleep(100000);
        semwait(semaforo,tenedor_d);
        printf("Filósofo %d comiendo\n",i);
        usleep(500000);
        semsignal(semaforo,tenedor_d);
        semsignal(semaforo,tenedor_i);

        semsignal(semaforo,HABITACION);

        usleep(500000);
    }
    exit(0);
}

int main()
{
    int i,p;

    semaforo = createsemarray(0x1234,FILOSOFOS+1);

    for(i=0;i<FILOSOFOS;i++) 
        initsem(semaforo,i,1);
    initsem(semaforo,HABITACION,FILOSOFOS-1);
    
    for(i=0;i<FILOSOFOS;i++) 
    {
        p = fork();
        if(p==0)
            filosofo(i);
    }

    for(i=0;i<FILOSOFOS;i++) 
        wait(NULL);

    erasesem(semaforo);
}