#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define SIZE 4000

#define INICIAL 900000000
#define FINAL 1000000000

int mat[SIZE][SIZE];

#define NTHREADS 8

void initmat(int mat[][SIZE]);
void printnonzeroes(int mat[SIZE][SIZE]);
int isprime(int n);
void printmat(int mat[][SIZE]);
void *tfunc(void *args);

void *tfunc(void *args)
{
  /* compute index ranges */
  int tnum = *((int *) args);
  int i_start = tnum * SIZE/NTHREADS;
  int i_end = (1+tnum) * SIZE/NTHREADS;  

  //printf("tnum %d i_start %d i_end %d\n",tnum, i_start, i_end);

  int i,j;
  for(i=i_start;i<i_end;i++)
    for(j=0;j<SIZE;j++)
      if(!isprime(mat[i][j])) {
	//printf("(%d,%d)=%d is not prime\n", i, j, mat[i][j]);
	mat[i][j]=0;
      }
}	


int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	int i;
	pthread_t tid[NTHREADS];
	int targs[NTHREADS];

	// Inicializa la matriz con números al azar
	initmat(mat);
	
	// Imprimit  la matriz
	//printmat(mat);

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	// Eliminar de la matriz todos los números que no son primos
	// Esta es la parte que hay que paralelizar
	for(i=0;i<NTHREADS;i++){
	  targs[i] = i;
	  pthread_create(&tid[i],NULL,tfunc,&targs[i]);
	}
	
	for(i=0;i<NTHREADS;i++)
	  pthread_join(tid[i],NULL);

	// Hasta aquí termina lo que se tiene que hacer en paralelo
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;


	printnonzeroes(mat);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}

void initmat(int mat[][SIZE])
{
	int i,j;
	int count=0;	
	srand(getpid());
	
	for(i=0;i<SIZE;i++)
	  for(j=0;j<SIZE;j++)
	    mat[i][j]=count++;
	    //mat[i][j]=INICIAL+rand()%(FINAL-INICIAL);
}

void printmat(int mat[][SIZE])
{
  int i,j;
	
  for(i=0;i<SIZE;i++)
    for(j=0;j<SIZE;j++)
      printf("%d ", mat[i][j]);
}

void printnonzeroes(int mat[SIZE][SIZE])
{
	int i,j;
	
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			if(mat[i][j]!=0)
				printf("%d\n",mat[i][j]);
}

			   
int isprime(int n)
{
	int d=3;
	int prime=n==2;
	int limit=sqrt(n);
	
	if(n>2 && n%2!=0)
	{
		while(d<=limit && n%d)
			d+=2;
		prime=d>limit;
	}
	return(prime);
}
