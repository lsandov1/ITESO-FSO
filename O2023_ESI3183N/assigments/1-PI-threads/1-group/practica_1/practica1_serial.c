#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define SECCIONES 20000000

#define ALTURA(a) (sqrt(1 - (a) * (a)))
#define AREA_TRAPECIO(a, b, c) ((c) * ((b) + ((a) - (b)) / 2))

double AREA_SECCION()
{
    double base = 1.0 / SECCIONES;
    double area = 0.0;
    double inc;

    double count = 0;
    int percent = 0;

    for (double i = 0; i < SECCIONES; i++)
    
    {
        if(count == SECCIONES/100){
            percent++;
            count = 0;
            printf("Avance : %d %%\n",percent);
        }
        double x1 = i * base;
        double x2 = (i + 1) * base;

        double y1 = sqrt(1 - (x1) * (x1));
        double y2 = sqrt(1 - (x2) * (x2));

        inc = base * (y1 + y2) / 2;
        area += inc;

        count++;
    }

    return area;
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

    double pi = AREA_SECCION();

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("------------------------------\n");
    printf("PI es igual a %f \n",pi*4);
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}



