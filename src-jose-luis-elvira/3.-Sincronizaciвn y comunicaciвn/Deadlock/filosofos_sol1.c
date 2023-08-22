#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "semaphoresarr.h"

#define FILOSOFOS 5

int semaforo;

void filosofo(int i) 
{
    int tenedor_i = i;
    int tenedor_d = (i + 1) % FILOSOFOS;
    int n = 10;

    // El último filósofo intercambia el orden de los tenedores izquierdo y derecho
    if(i==FILOSOFOS-1)
    {
        tenedor_i = (i + 1) % FILOSOFOS;
        tenedor_d = i;
    }

    while(n--)
    {
        semwait(semaforo,tenedor_i);
        usleep(100000);
        semwait(semaforo,tenedor_d);
        printf("Filósofo %d comiendo\n",i);
        usleep(500000);
        semsignal(semaforo,tenedor_d);
        semsignal(semaforo,tenedor_i);
        usleep(500000);
    }
    exit(0);
}

int main()
{
    int i,p;

    semaforo = createsemarray(0x1234,FILOSOFOS);

    for(i=0;i<FILOSOFOS;i++) 
        initsem(semaforo,i,1);
    
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