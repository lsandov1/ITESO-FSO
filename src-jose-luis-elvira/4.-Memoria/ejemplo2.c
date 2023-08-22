#include <stdio.h>

int global = 100;

void saludar() 
{
    printf("Hola mundo\n");
}

int main()
{
    int local=0;
    void *ptr;
    int *iptr;

    printf("Dirección de memoria de global = %p\n",&global);
    printf("Dirección de memoria de local = %p\n",&local);
    printf("Dirección de memoria de la función saludar = %p\n",saludar);

    ptr = &global;
    iptr = ptr;
    printf("El contenido antes del incremento de *iptr(global) es %d\n",*iptr);
    (*iptr)++;
    printf("El valor icrementado en *iptr (global) es %d\n",*iptr);

    ptr = &local;
    iptr = ptr;
    printf("El contenido antes del incremento de *iptr(local) es %d\n",*iptr);
    (*iptr)++;
    printf("El valor icrementado en *iptr (local) es %d\n",*iptr);

    ptr = saludar;
    iptr = ptr;
    printf("El contenido antes del incremento de *iptr(saludar) es %d\n",*iptr);
    (*iptr)++;
    printf("El valor icrementado en *iptr (saludar) es %d\n",*iptr);


}