#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *g;

int main()
{
    int p;

    g = malloc(sizeof(int));
    *g = 5;

    p = fork();
    if(p==0)
    {
        while(*g<10) 
        {
            printf("En el hijo *g, dirección %p = %d\n",g,*g);
            (*g)++;
            sleep(1);
        }
    }
    else
    {
        while(*g>0) 
        {
            printf("En el padre *g, dirección %p  = %d\n",g,*g);
            (*g)--;
            sleep(1);
        }

    }    
}