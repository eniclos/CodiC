#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{

	int fd[2];
	pid_t pid;
	char saludopare[] = "Bon dia fill\0";
	char buffer[80];

	pipe(fd);	  //crea el pipe
	pid = fork(); //crea un procés FILL

	switch (pid)
	{
	case -1: //ERROR
		printf("No s'ha pogut crear FILL\n");
		exit(-1);

	case 0:											 //FILL
		close(fd[1]);								 //tanca el descriptor d'escriptura
		read(fd[0], buffer, strlen(saludopare) + 1); //llig del pipe
		printf("\tFILL. Missatge llegit: %s\n", buffer);
		break;

	default:											  //PARE
		close(fd[0]);									  //tanca el descriptor d'entrada
		write(fd[1], saludopare, strlen(saludopare) + 1); //escriu al pipe
		printf("PARE escriu al pipe...\n");
		wait(NULL); //espera al procés fill
	}
	return 0;
}
