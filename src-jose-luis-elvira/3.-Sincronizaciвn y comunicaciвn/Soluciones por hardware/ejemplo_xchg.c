#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Macro que incluye el código de la instrucción máquina xchg
#define atomic_xchg(A,B) 	__asm__ __volatile__(	\
							"   lock xchg %1,%0 ;\n"	\
							: "=ir"  (A)			\
							: "m"  (B), "ir" (A)		\
							);

#define NTHREADS 5
#define ITERS 10

int g=0;


void *tfunc(void *args)
{
	int i = *((int *) args);
	int n=ITERS;
	int l=1;
	
	while(n--)
	{
		// Sección de entrada
		do { atomic_xchg(l,g); } while(l!=0);
		
        // Sección crítica
        printf("Hilo %d entra a la sección crítica",i);
        fflush(stdout);
        usleep(rand()%4000000);
        printf("-Hilo %d sale de la sección crítica\n",i);
        fflush(stdout);
				
		// Sección de salida
		g=0;
		l=1;
		
		// Sección restante
		usleep(rand()%1000000);
	}
}

int main()
{
	int i;
	pthread_t tid[NTHREADS];
	int args[NTHREADS];
	
	srand(getpid());

	for(i=0;i<NTHREADS;i++)
	{
		args[i] = i;
		pthread_create(&tid[i],NULL,tfunc,&args[i]);
	}
	
	for(i=0;i<NTHREADS;i++)
		pthread_join(tid[i],NULL);
}