#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

/* Calcular el valor de PI a través de la regla del trapecio. */

/* La regla del trapecio es un método de aproximación a la integral definida de una */
/* función. Se basa en la idea de aproximar el área bajo una curva mediante una serie */
/* de trapecios en lugar de rectángulos, lo que proporciona una estimación más */
/* precisa. */

/* En este caso tenemos la función f(x) = sqrt(1-y2), que si graficamos esta función de */
/* 0 a 1 nos da como resultado un cuarto de círculo. Para hacer el cálculo de PI es */
/*    necesario calcular el área que hay debajo del cuarto del círculo y el resultado */
/* multiplicarlo por 4. */

/* Para calcular el área que está debajo del cuarto de círculo vamos a usar la regla del */
/* trapecio. Esta consiste en dividir el intervalo de 0 a 1 en n intervalos con los que */
/* formaremos pequeños rectángulos. Para cada uno de los rectángulos vamos a */
/* calcular la altura f(x) tomando x a la mitad del rectángulo, para que con esa altura */
/* multiplicada por la base del rectángulo obtenemos el área de cada uno de los */
/* rectángulos. La suma del área de todos los rectángulos será PI/4. Mientras más */
/* sean los rectángulos y más pequeños, el valor obtenido será más preciso. */

#define ITERS 100000000

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	int n;
	double sum = 0.0;
	double x=0;
	double y;
	double delta=1.0/ITERS;
	double hdelta=delta/2;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	for(n=1;n<ITERS;n++)
	  {
	  x += delta;
	  y = sqrt(1-pow(x-hdelta,2));
	  sum += delta*y;
	  }

	sum *= 4;

	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("%.32lf %.32lf \n", sum, M_PI);
}
