#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    int fd[2];
    char buffer[30];
    pid_t pid;

    pipe(fd);     //creació del pipe
    pid = fork(); //creació del FILL

    switch (pid)
    {
    case -1: //error
        printf("No s'ha pogut crear el FILL\n");
        exit(-1);
        break;

    case 0: // fill
        printf("FILL escrivint al pipe... \n");
        write(fd[1], "Hola papi", 10);
        break;

    default: // pare
        wait(NULL);
        sleep(2);
        printf("PARE llegint del pipe... \n");
        read(fd[0], buffer, 24);
        printf("\t Missatge llegit: %s \n", buffer);
        break;
    }
    return 0;
}
