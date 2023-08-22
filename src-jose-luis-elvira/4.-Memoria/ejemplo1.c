#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g;

void proc(int n)
{
    int i;
    g=n;
    for(i=0;i<10;i++) 
    {
        printf("El dato en %p es %d\n",&g,g);
        sleep(1);
    }

    exit(0);

}

int main()
{
    
    int p;
    
    p=fork();

    if(p==0)
        proc(0);
    else
        proc(1);
}