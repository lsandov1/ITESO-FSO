#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define NTHREADS 4
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define SECCIONES 50000000 // define el numero de secciones en las que se va a dividir el cuarto de circulo
#define ALTURA(a) (sqrt(1 - (a) * (a)))
#define AREA_TRAPECIO(a, b, c) ((c) * ((b) + ((a) - (b)) / 2))

double AREA = 0.0;

struct ThreadArgs
{
    double inicio;
    double final;
};

void *AREA_SECCION(void *arg)
{
    struct ThreadArgs *args = (struct ThreadArgs *)arg;

    double inicio = args->inicio;
    double final = args->final;

    printf("%lf %lfd\n",inicio,final);

    double inc;
    double base = (1.0 / (SECCIONES))/NTHREADS;
    double area = 0.0;
    
    double count = 0;
    int percent = 0;

    for (double i = inicio; i < final; i++)
    {
        if(count == SECCIONES/100){
            percent++;
            count = 0;
            printf("El avance de la seccion que inicia en %f es de %d %%\n",inicio,percent);
        }
        double x1 = i * base;
        double x2 = (i+1) * base; 
        

        double y1 = sqrt(1 - (x1) * (x1));
        double y2 = sqrt(1 - (x2) * (x2)); 



        
        //inc = base * (y1+y2)/2;
        inc = base * (y1+y2)/2;
        pthread_mutex_lock(&mutex);
        AREA+=inc;
        pthread_mutex_unlock(&mutex);

        count++;

        
    }
  //  printf("%f\n",AREA);
    return NULL;
}

int main()
{
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    // se usa para calcular el timpo que tomo la ejecución del programa
    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    pthread_t tid[NTHREADS];
    struct ThreadArgs threadArgs[NTHREADS];

    for (int i = 0; i < NTHREADS; i++)
    {
        threadArgs[i].inicio = i * SECCIONES;
        threadArgs[i].final = (i+1) * SECCIONES;
    }


    for (int i = 0; i < NTHREADS; i++)
    {

        pthread_create(&tid[i], NULL, AREA_SECCION, &threadArgs[i]);
    }

    for (int i = 0; i < NTHREADS; i++)
        pthread_join(tid[i], NULL);

    // Hasta aquí termina lo que se tiene que hacer en paralelo
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("------------------------------\n");
    printf("PI es igual a %f \n",AREA*4);
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}