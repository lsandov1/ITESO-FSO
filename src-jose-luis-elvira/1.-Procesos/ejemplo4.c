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
            printf("En el hijo i = %d\n",i);
            sleep(2);
        }
    }
    else // En el padre
    {
        for(i=4;i>0;i--)
        {
            printf("En el padre i = %d\n",i);
            sleep(2);
        }
    }
}