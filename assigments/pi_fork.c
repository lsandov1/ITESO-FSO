#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <math.h>

#define NPROCS 8
#define ITERS 100000000

double *g;

void tfunc(int i)
{
    double x = (double)i/NPROCS;
    double sum = 0.0;
    double y;
    double delta=1.0/ITERS;
    double hdelta=delta/2;
    int n;

    for(n=0;n<ITERS/NPROCS;n++)
      {
	x += delta;
	y = sqrt(1-pow(x-hdelta,2));
	sum += delta*y;
      }

    g[i]=sum;

    printf("i = %d x = %lf PID = %d sum = %.16lf\n", i, x, getpid(), sum);
}

int main()
{
  int pid;
  int i;
  double total_sum = 0;	

  int shmid = shmget(0x1234,sizeof(double)*NPROCS, 0666|IPC_CREAT);
  g = (double *)shmat(shmid,NULL,0);

  // compute partial results
  for(i=0;i<NPROCS;i++) {
    pid=fork();
    if(pid==0) {
      tfunc(i);
      exit(0);
    }
  }

  // sum partial results
  for(i=0;i<NPROCS;i++) {
    wait(NULL);
    //printf("g[i]= %lf total_sum = %lf\n", g[i], total_sum);
    total_sum += g[i];
  }

  total_sum *= 4;
  printf("%.32lf %.32lf \n", total_sum, M_PI);
}
