#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "semaphoresarr.h"

int semarr;
// #define SYNC 0
// #define SYNC2 1

//     =0 
enum {SYNC};

void imprime(char *s)
{
	usleep(rand()%100000);
	printf("%s\n",s);
	usleep(rand()%100000);
}

void P()
{
	semwait(semarr,SYNC);
	imprime("A");
	imprime("B");
	imprime("C");
	exit(0);
}

void Q()
{
	imprime("D");
	imprime("E");
	semsignal(semarr,SYNC);

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
