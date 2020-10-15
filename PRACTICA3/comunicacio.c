/*
Programa de comunicació inicial mitjançant 
un fitxer com a canal de comunicació
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void main()
{
    char saludo[] = "Salutacions....";
    char buffer[10];
    int fd, status, bytesllegits;
    pid_t pid;

    fd = open("text.txt", O_WRONLY); //fitxer obert para escriptura

    //control de l'error en apertura fitxer
    if (fd == -1)
    {
        printf("ERROR a l'obrir el fitxer");
        exit(-1);
    }

    if ((pid = fork()) == 0)
    { //Procés FILL

        // escriu saludo a fitxer i tanca
        printf("FILL > Escric la salutació al fitxer...\n");
        write(fd, saludo, strlen(saludo));
        close(fd);
    }
    else
    { //Procés PARE
        // Esperem que el fill acabe
        waitpid(pid, &status, 0);

        fd = open("text.txt", O_RDONLY); // fitxer obert para lectura
        printf("PARE > Contigut del fitxer: \n");

        //llig bytes d'un en un i ho desa al buffer
        bytesllegits = read(fd, buffer, 1);

        while (bytesllegits != 0)
        {
            printf("%s", buffer);               //escriu byte llegit
            bytesllegits = read(fd, buffer, 1); //llig altre byte
        }
        close(fd);
    }
}
