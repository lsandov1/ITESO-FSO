#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

bool flag[2] = {false,false};
int turno = 0;

void *thread(void *args)
{
    int i = *((int *) args);
    int j = 1 - i;
    int n = 10;

    while(n--)
    {
        // Sección de entrada
        flag[i] = true;
        turno = j;
        while(flag[j])
        {
            flag[i] = false;
            while(turno!=i);
            flag[i] = true;
        }

        // Sección crítica
        printf("Hilo %d entra a la sección crítica",i);
        fflush(stdout);
        usleep(rand()%4000000);
        printf("-Hilo %d sale de la sección crítica\n",i);
        fflush(stdout);

        // Salida
        flag[i] = false;
        turno = j;

        // Sección restante
        usleep(rand()%1000000);
    }
}


int main()
{
    pthread_t tid[2];
    int targs[2];
    int i;

    srand(getpid());
    for(i=0;i<2;i++)
    {
        targs[i] = i;
        pthread_create(&tid[i],NULL,thread,&targs[i]);
    }

    for(i=0;i<2;i++)
        pthread_join(tid[i],NULL);
}