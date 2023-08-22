#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define JUGADORES 4

#define BLOCKING 0
#define NON_BLOCKING IPC_NOWAIT


struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    int x;    /* message data */
};

int queue_id;	// Buzón de mensajes

void jugador(int i)
{
	struct msgbuf mensaje;
	int vueltas = 10;

	int next = i % JUGADORES + 1;

	while(vueltas--)
	{
		msgrcv(queue_id,&mensaje,sizeof(struct msgbuf),i,BLOCKING);
		printf("Jugador %d inicia su turno ",i);
		fflush(stdout);
		sleep(1);
		mensaje.mtype = next;
		printf("- Jugador %d termina su turno\n",i);
		msgsnd(queue_id,&mensaje,sizeof(struct msgbuf),NON_BLOCKING);
	}
	exit(0);
}

int main()
{
	int i;
	int p;
	struct msgbuf mensaje;

	// Crear buzones
	// Crear buzón de mensajes 
	queue_id=msgget(0x5678,0666|IPC_CREAT);
	if(queue_id==-1)
	{
		fprintf(stderr,"No se pudo crear el buzón\n");
		exit(1);
	}


	for(i=0;i<JUGADORES;i++)
	{
		p=fork();
		if(p==0)
			jugador(i+1);
	}

	mensaje.mtype = 1;
	msgsnd(queue_id,&mensaje,sizeof(struct msgbuf),NON_BLOCKING);


	for(i=0;i<JUGADORES;i++)
		wait(NULL);

	msgctl(queue_id, IPC_RMID, NULL);

}
