#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define NTHREADS 5

#define EN_SR 0

bool seleccionando[NTHREADS];
int numero[NTHREADS];

int max(int *n)
{
	int i;
	int maxval=0;
	for(i=0;i<NTHREADS;i++)
		if(n[i]>maxval)
			maxval = n[i];
	return(maxval);
}

void *thread(void *args)
{
    int i = *((int *) args);
    int j;
    int n = 10;

    while(n--)
    {
        // Sección de entrada
        seleccionando[i] = true;
        numero[i] = max(numero) + 1;
		seleccionando[i] = false;
        for(j=0;j<NTHREADS;j++)
		{
			while(seleccionando[j]);
			while(numero[j]!=EN_SR && 
				  (numero[j]<numero[i] || numero[j]==numero[i] && j<i));
		}


        // Sección crítica
        printf("Hilo %d entra a la sección crítica",i);
        fflush(stdout);
        usleep(rand()%4000000);
        printf("-Hilo %d sale de la sección crítica\n",i);
        fflush(stdout);

        // Salida
        numero[i] = EN_SR;

        // Sección restante
        usleep(rand()%1000000);
    }
}


int main()
{
    pthread_t tid[NTHREADS];
    int targs[NTHREADS];
    int i;

    srand(getpid());
	
	// Iniciliza datos compartidos
	for(i=0;i<NTHREADS;i++)
	{
		seleccionando[i] = false;
		numero[i] = 0;
	}
		
    
    for(i=0;i<NTHREADS;i++)
    {
        targs[i] = i;
        pthread_create(&tid[i],NULL,thread,&targs[i]);
    }

    for(i=0;i<NTHREADS;i++)
        pthread_join(tid[i],NULL);
}