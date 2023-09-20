#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define ITERS 100000000
#define NPROCS 4

struct x_region {
  int i;
  double sum;
};
struct x_region x_regions[NPROCS];
struct x_region *m,*g;

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

    g->i=i;
    g->sum=sum;

    printf("i = %d PID = %d sum = %.16lf\n", i, getpid(), sum);
}

int main()
{
  int pid,ppid;
  int i;
  double total_sum = 0;	

  int shmid = shmget(0x1234,sizeof(x_regions),0666|IPC_CREAT);
  m = shmat(shmid,NULL,0);
  g = m;

  ppid=getpid();

  // compute partial results
  for(i=0;i<NPROCS;i++, g++) {
    pid=fork();
    if(pid==0)
      tfunc(i);
    else {
      wait(NULL);
      shmdt(shmid);
    }
  }

  if(getpid() == ppid) {
    // sum partial results
    for(i=0,g=m;i<NPROCS;i++, g++)
      total_sum += g->sum;

    total_sum *= 4;
    printf("PID = %d PI = %.16lf\n", getpid(), total_sum);
  }
}
