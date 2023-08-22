#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


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
	imprime("C");
	exit(0);
}

void Q()
{
	imprime("D");
	imprime("E");
	exit(0);
}

int main() 
{
	int p;
	
	srand(getpid());
	
	p=fork();
	if(p==0)
		P();

	p=fork();
	if(p==0)
		Q();

	wait(NULL);
	wait(NULL);
}
