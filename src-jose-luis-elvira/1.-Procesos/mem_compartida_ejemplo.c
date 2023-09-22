#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

int *g;

int main()
{
	int pid;
	int i;
	
	int shmid = shmget(0x1234,sizeof(int),0666|IPC_CREAT);
	g = shmat(shmid,NULL,0);
	
	*g=0;
		
	pid=fork();
	// Todas las variables locales y globales se 
	// duplican
	
	if(pid==0)	// El hijo
	{
		for(i=0;i<5;i++)
		{
			(*g)++;
			printf("En el hijo g=%d\n",*g);
			sleep(1);
		}
	}
	else
	{
		for(i=0;i<10;i++)
		{
			printf("En el padre g=%d\n",*g);
			sleep(1);
		}
		shmdt(shmid);
	}
	
}
