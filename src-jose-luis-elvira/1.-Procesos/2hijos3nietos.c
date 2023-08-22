#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void nieto(int n)
{
    printf("Soy el proceso nieto %d, pid = %d\n",n,getpid());
    sleep(20);
    exit(0);
}

void hijo(int n)
{
    int p,i;

    printf("Soy el proceso hijo %d, pid = %d\n",n,getpid());
    for(i=0;i<3;i++)
    {
        p=fork();
        if(p==0)
            nieto(i);
    }

    for(i=0;i<3;i++)
        wait(NULL);

    exit(0);
}

int main()
{
    int p,i;

    for(i=0;i<2;i++)
    {
        p=fork();
        if(p==0)
            hijo(i);
    }
    
    sleep(3);
    kill(0,9);

    for(i=0;i<2;i++)
        wait(NULL);
}
