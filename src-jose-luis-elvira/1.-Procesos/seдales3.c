#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int g=0;

void sighand(int signum)
{
    // Cuando llegue la señal, ponga la variable g = 5
    printf("Recibí la señal %d\n",signum);
    g=5;
}

int main()
{
    int p;

    // Al iniciar instala un manejador de señal
    signal(10,sighand);

    p=fork();
    if(p==0)    // Hijo
    {
        while(1) 
        {
            sleep(15);              // Espera 15 segundos
            kill(getppid(),10);     // Envia la señal 1 al padre
        }
    }
    else
    {           // Proceso padre
        while(1)
        {
            while(g>0)      // Decrementa g hasta llegar a 0
            {
                printf("g=%d\n",g);
                sleep(1);
                g--;
            }
            while(g==0); // Espera a que g tenga un valor diferente de 0
        }
    }
}