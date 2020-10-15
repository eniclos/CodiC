#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void main()
{

    pid_t pid, fill_pid, pid2, fill2_pid;
    int fdA[2];
    int fdB[2];

    char saludoavi[] = "Salutacions de l'avi..\n";
    char saludonet[] = "Salutacions del net..\n";

    char buffer[80] = "";

    pipe(fdA);
    pipe(fdB);

    pid = fork(); //Soc l'avi cree al pare

    if (pid == -1)
    { //error
        printf("No s'ha pogut crear el procés pare...\n");
        exit(-1);
    }

    if (pid == 0)
    {                  //estem al procés pare
        pid2 = fork(); //Soc el pare, cree a net
        switch (pid2)
        {

        case -1: //error
            printf("No s'ha pogut crear el procés NET en el PARE");
            exit(-1);
            break;

        case 0: //procés net
            //net reb
            close(fdB[1]);                        //tanca descriptor entrada
            read(fdB[0], buffer, sizeof(buffer)); //llig el pipe
            printf("NET reb missatge de PARE: %s\n", buffer);

            //net envia
            printf("NET envia missatge a PARE..\n");
            close(fdA[0]);
            write(fdA[1], saludonet, strlen(saludonet)); //escriu el pipe
            break;

        default: //procés pare
            //pare reb de avi
            close(fdA[1]);                        //tanca descriptor entrada
            read(fdA[0], buffer, sizeof(buffer)); //llig el pipe
            printf("PARE reb missatge de AVI: %s\n", buffer);

            //pare envia a net
            printf("PARE envia missatge a NET..\n");
            close(fdB[0]);
            write(fdB[1], buffer, strlen(buffer)); //escriu el pipe
            fill2_pid = wait(NULL);                        //Espera a finalització del fill

            //pare reb de net
            close(fdA[1]);                        //tanca descriptor entrada
            read(fdA[0], buffer, sizeof(buffer)); //llig el pipe
            printf("PARE reb missatge de NET: %s\n", buffer);

            //pare envia a avi
            printf("PARE envia missatge a AVI...\n");
            close(fdB[0]);
            write(fdB[1], buffer, strlen(buffer)); //escriu el pipe
        }                                                  //fi casos fill (pare de net)

    } //fi procés fill
    else
    { //procés avi
        //avi envia
        printf("AVI envia missatge a PARE..\n");
        close(fdA[0]);

        write(fdA[1], saludoavi, strlen(saludoavi)); //escriu el pipe
        fill_pid = wait(NULL);                        //Espera a la finalització del fill

        //pare reb
        close(fdA[1]);                        //tanca descriptor entrada
        read(fdB[0], buffer, sizeof(buffer)); //llig  el pipe
        printf("AVI reb missatge de PARE: %s\n", buffer);

    } //fi procés avi

    exit(0);
}
