#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i;

int main()
{
    int p;

    p = fork();
    if(p==0)    // Es 0 en el hijo
    {
        for(i=0;i<8;i++) 
        {
            printf("En el hijo(%d) i = %d\n",getpid(),i);
            sleep(2);
        }

        exit(0);
    }
 
    for(i=4;i>0;i--)
    {
        printf("En el padre (%d) i = %d\n",getpid(),i);
        sleep(2);
    }
 }