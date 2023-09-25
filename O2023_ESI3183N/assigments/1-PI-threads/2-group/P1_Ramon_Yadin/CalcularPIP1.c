#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4
#define itervalo 1000000

float total=0;
void *tfunc(void *args){

    int tnum = *((int *) args);
    // long int itervalo = 1000000000;
    int inicio = tnum * (itervalo/NTHREADS);
    int fin = inicio + (itervalo/NTHREADS);
    double sum;
    double x; // punto medio de cada trapecio
    double y; // Tamaño del intervalo
    int i;

    printf("Hilo %d, desde %d hasta %d\n",tnum,inicio,fin-1);
    

    y = 1.0 / itervalo;

    for (i = inicio; i < fin; i++) 
    {
        x = (i + 0.5) * y; //formula
        sum += 4.0 / (1.0 + x * x); // Se suma el acumulador y se evalua con la formula 1/(1+x^2), pero en nuestros datos
    }
    total  += (sum * y);

    printf("El valor del hilo %d es de: %.4f \n",tnum, (sum * y)) ; // regresa el resultado de la suma, multiplicado por x
    // printf("HASta ahora va %f \n",total);
}

int main() 
{
    pthread_t tid[NTHREADS];
    int targs[NTHREADS];
    int i;
    struct timeval start, end;
    double Time;

    gettimeofday(&start, NULL); // Tiempo inicial
    // printf("Total: %f \n", total);
    for(i=0; i<NTHREADS; i++){
        targs[i] = i;
        pthread_create(&tid[i],NULL,tfunc,&targs[i]);
    }
    for(i=0; i<NTHREADS; i++){
        pthread_join(tid[i],NULL);
    }
    

    gettimeofday(&end, NULL); // Tiempo final


    Time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0; // Tiempo en segundos
    printf("El valor total de PI es %.15f \n", total);
    printf("El tiempo fue de: %f segundos\n", Time);

    return 0;
}




