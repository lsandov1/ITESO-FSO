#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    char *cmdargs[16];
    char str[80];
    int retval;
    int i;
    int p;

    while(1)
    {
        printf("my_shell>");
		
        fgets(str,80,stdin);
        str[strcspn(str,"\n")]='\0';
		
		i=0;
        cmdargs[i] = strtok(str," ");	// Separamos el comando

		if(cmdargs[i]==NULL)			// Si está vacio, pedir otro comando
			continue;		

		if(strcmp(cmdargs[i],"exit")==0)		// Si es exit, salir
			break;

		while(cmdargs[i]!=NULL)			// Separamos los argumentos
		{
            i++;
			cmdargs[i]=strtok(NULL," ");
		}

        p = fork();
        if(p==0)
		{
			// Si el programa a ejecutar tiene error, salimos
            if(execvp(cmdargs[0],cmdargs)!=0)
				exit(1);
		}
		
        wait(&retval);
		if(retval!=0)
			fprintf(stderr,"Programa incorrecto\n");
	
    } 
}
