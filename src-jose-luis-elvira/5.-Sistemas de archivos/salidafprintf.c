#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int i;

    for(i=0;i<10;i++) 
    {
        fprintf(stderr,"%d ",i);
        sleep(1);
    }
}