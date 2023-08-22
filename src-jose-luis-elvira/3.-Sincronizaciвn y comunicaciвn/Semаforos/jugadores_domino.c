#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "semaphoresarr.h"

#define JUGADORES 4
#define JUGADAS 10

int semid;

void jugador(int i)
{
    int next = (i+1)%JUGADORES;
    int n=JUGADAS;

    while(n--)
    {
        semwait(semid,i);
        printf("Jugador %d inicia su jugada",i);
        fflush(stdout);
        sleep(1);
        printf("-Jugador %d termina su jugada\n",i);
        semsignal(semid,next);
    }
    exit(0);
}


int main()
{
    int i,p;

    semid = createsemarray(0x1232,JUGADORES);
    for(i=0;i<JUGADORES;i++) 
        initsem(semid,i,0);

    for(i=0;i<JUGADORES;i++)
    {
        p=fork();
        if(p==0)
            jugador(i);
    }

    sleep(5);
    semsignal(semid,0);

    for(i=0;i<JUGADORES;i++)
        wait(NULL);

    erasesem(semid);
}