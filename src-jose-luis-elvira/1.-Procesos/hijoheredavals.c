#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g = 0;

int main()
{
    int p;

    g = 5;
    p = fork();
    if(p==0)
    {
        while(g<10) 
        {
            printf("En el hijo g = %d\n",g);
            g++;
            sleep(1);
        }
    }
    else
    {
        while(g>0) 
        {
            printf("En el padre g = %d\n",g);
            g--;
            sleep(1);
        }

    }    
}