#include <stdio.h>

int main()
{
    FILE *fp;

    fp = fopen("hola.txt","w");

    fprintf(stderr,"Esta es una prueba\n");

    fclose(fp);
}