#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int i=10;
    printf("Hola, mi pid es %d %d\n",getpid(),i);
    fork();
    printf("Adios, mi pid es %d %d\n",getpid(),i);
}
