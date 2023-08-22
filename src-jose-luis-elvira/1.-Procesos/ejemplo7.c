#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int i;

int main()
{
    int p;
    int retval;

    p = fork();
    if(p==0)    // Es 0 en el hijo
    {
        printf("Inicia proceso hijo pid = %d\n",getpid());
        for(i=0;i<8;i++) 
        {
            printf("En el hijo(%d) i = %d\n",getpid(),i);
            sleep(2);
        }

        exit(5);
    }
 
    for(i=4;i>0;i--)
    {
        printf("En el padre (%d) i = %d\n",getpid(),i);
        sleep(2);
    }

    p = wait(&retval);
    printf("El hijo %d termiinó con código %x\n",p,retval>>8);
 }