#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int ppid = getpid();

    fork();
    fork();
    fork();
    printf("Adios, mi pid es %d %d %d\n",getpid(),ppid, getpid()-ppid);
    wait(NULL);
}
