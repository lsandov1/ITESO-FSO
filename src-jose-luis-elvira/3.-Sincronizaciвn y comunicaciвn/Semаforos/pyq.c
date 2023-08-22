#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "semaphoresarr.h"

int semarr;
#define SYNC 0

void imprime(char *s)
{
	usleep(rand()%100000);
	printf("%s\n",s);
	usleep(rand()%100000);
}

void P()
{
	imprime("A");
	imprime("B");
	semsignal(semarr,SYNC);
	imprime("C");
	exit(0);
}

void Q()
{
	semwait(semarr,SYNC);
	imprime("D");
	imprime("E");
	exit(0);
}

int main() 
{
	int p;
	
	// Solicitar al SO que me de un arreglo de semáforos
	semarr = createsemarray(0x4321,1);
	initsem(semarr,SYNC,0);	// Inicializamos el semáforo 0 del arreglo con 1

	srand(getpid());
	
	p=fork();
	if(p==0)
		P();

	p=fork();
	if(p==0)
		Q();

	wait(NULL);
	wait(NULL);

	erasesem(semarr);
}
