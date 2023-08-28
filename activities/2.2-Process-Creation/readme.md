Los siguientes ejercicios requieren que desarrolles 6 programas en lenguaje C, sube cada uno de los archivos .c a Canvas

Para la pregunta 6, sube un documento en formato PDF de media cuartilla

1.-Escribir un programa que cree un hijo. El hijo debe escribir: "Soy el hijo" diez veces. El padre debe escribir: "Soy el padre" diez veces. Ambos procesos deberán mostrar concurrentemente sus líneas en pantalla y entre cada linea que escriban deben hacer una pausa de un segundo. El padre debe esperar a que termine el hijo y mostrar el mensaje: "Mi proceso hijo ya ha terminado".

Sube este programa como ejer1.c

2.-Desarrolla un programa que reciba como argumento desde la línea de comandos un valor de entrada n cuyo significado sera nivel. Ese nivel tendrá el significado de cuántos niveles tendrá un árbol de procesos y al finalizar deberá haber 2n procesos donde cada proceso deberá ir mostrando en pantalla  un número que será el nivel en el que se encuentre actualmente, de manera que cada uno de los procesos estará mostrando en pantalla todos los niveles por los que va pasando. Por ejemplo:

    Si n=1 terminarán dos procesos que deberán mostrar en pantalla 0,1,1
    Si n=2 terminarán cuatro procesos que deberán mostrar en pantalla 0,1,1,2,2,2,2
    Si n=4 terminarán 16 procesos que deberán mostrar en pantalla 0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4

No es necesario que los números que se van mostrando en pantalla se muestren en orden.

Sube este programa como ejer2.c

3.- Desarrolla un programa que reciba como argumento desde la línea de comandos un valor de entrada n cuyo significado sera un número de procesos a crear, de manera que cuando ejecutes tu programa este será el proceso padre que creará solamente n procesos hijos a un nivel, cada proceso hijo mostrará su número que será de 1 hasta n. El proceso padre deberá esperar a que  todos los hijos terminen para al finalizar mostrar en pantalla el mensaje "Fin". Por ejemplo:

$ ./programa 5
Proceso hijo 1
Proceso hijo 2
Proceso hijo 3
Proceso hijo 4
Proceso hijo 5
Fin

 No te preocupes si las salidas en pantalla no están en orden.

Sube este programa como ejer3.c

 

4.- Desarrolla un programa que solicite al usuario una cadena de caracteres, esa cadena será el nombre de un programa1 a ejecutarse, una vez que este programa termine de ejecutarse permitirá al usuario introducir otro programa a ejecutarse, esto terminará cuando el usuario introduzca exit. Para este ejercicio utiliza la llamada al sistema system(). En este ejercicio estamos haciendo nuestro primer shell o intérprete de comandos.

Sube este programa como ejer4.c

 

5.- Repite el ejercicio anterior, pero ahora no podrás usar la llamada al sistema system(), por lo que será necesario que crees un nuevo proceso (hijo) el cuál ejecutará el programa que indicaste; Una vez que termine el programa de ejecutarse permitirá al usuario introducir otro programa a ejecutarse, esto terminará cuando el usuario introduzca exit.

Sube este programa como ejer5.c.

 

6.- ¿Qué fue lo que aprendiste?

sube un documento en formato PDF de media cuartilla

 

1Puedes usar el siguiente programa para hacer pruebas con los ejercicios 4 y 5

#include <stdio.h>
#include <unistd.h>

int main()
{
	sleep(10);
	printf("Hola mundo\n"),
	sleep(2);
}

Todo el material de esta actividad se encuentra en 'Previo Sesion '3
