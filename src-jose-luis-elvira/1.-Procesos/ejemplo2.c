#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Hola, mi pid es %d\n",getpid());
    fork();
    printf("Otra vez hola desde %d\n",getpid());
    fork();
    printf("Adios, mi pid es %d\n",getpid());
}