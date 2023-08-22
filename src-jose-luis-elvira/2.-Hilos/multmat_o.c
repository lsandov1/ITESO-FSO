#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAM 2000

double a[TAM][TAM], b[TAM][TAM], c[TAM][TAM];

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;


    int i,j,k;

	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    for(i=0;i<TAM;i++)
        for(k=0;k<TAM;k++)
            for(j=0;j<TAM;j++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}