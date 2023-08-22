#include <stdio.h>

char buffer[30];

void saludar() 
{
    printf("Hola mundo\n");
}

int main()
{
    void (*funcptr)();
    void *ptr;
    char *charfuncptr;
    int i;

    ptr = saludar;
    funcptr = ptr;
    charfuncptr = ptr;

    funcptr();

    printf("La función saludar mide %ld bytes\n",((void *)main)-((void *)saludar));

    // Copiar todos los bytes de la función al buffer
    ptr = saludar;
    funcptr = ptr;
    for(i=0;i<30;i++)
        buffer[i] = charfuncptr[i];

    printf("\nTodos los bytes de la función saludar\n");
    for(i=0;i<26;i++)
    {
        printf("%X ",*((char *)(ptr+i)));
    }

    printf("\nTodos los bytes del buffer\n");
    for(i=0;i<26;i++)
    {
        printf("%X ",buffer[i]);
    }

    printf("\n");
    // Apuntar con el apuntador a la función al buffer y ejecutar
    ptr = buffer;
    funcptr = ptr;
    funcptr();
}