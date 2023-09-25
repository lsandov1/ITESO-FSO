#include <stdio.h>
#include <sys/time.h>

double Pi2(int itervalo) 
{
    double sum;
    double x; // punto medio de cada trapecio
    double y; // Tamaño del intervalo
    int i;

    y = 1.0 / itervalo;

    for (i = 0; i < itervalo; i++) 
    {
        x = (i + 0.5) * y; //formula
        sum += 4.0 / (1.0 + x * x); // Se suma el acumulador y se evalua con la formula 1/(1+x^2), pero en nuestros datos
    }

    return sum * y; // regresa el resultado de la suma, multiplicado por x
}

int main() 
{
    int itervalo = 1000000;

    struct timeval start, end;
    double Time;

    gettimeofday(&start, NULL); // Tiempo inicial

    double pi = Pi2(itervalo); // Manadar los intervalos a la función

    gettimeofday(&end, NULL); // Tiempo final


    Time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0; // Tiempo en segundos


    printf("El valor de PI es: %f\n", pi);

    printf("El tiempo fue de: %f segundos\n", Time);

    return 0;
}

