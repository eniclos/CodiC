#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

//=======================================================================

void manejador_senyal(int senyal)
{

    int pidc, pidd;

    printf("INICI MANEJADOR\n");

    if ((pidc = fork()) == 0)
    { //fill C
        printf("\tSoc el fill C(%d) de A(%d)\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }

    sleep(1);

    if ((pidd = fork()) == 0)
    { //fill D
        printf("\tSoc el fill D(%d) de A(%d)\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    printf("FI MANEJADOR\n");
}

//=======================================================================

int main()
{

    pid_t pida, pidb, pide, pidf, pidg;
    int status, op1, op2;

    printf("Introdueix PRIMER operand: \n");
    fflush(stdin);
    scanf("%d", &op1);

    printf("Introdueix SEGON operand: \n");
    fflush(stdin);
    scanf("%d", &op2);

    pida = getpid();
    //establiment del senyal amb el manejador
    signal(SIGUSR1, manejador_senyal);

    if ((pidb = fork()) == 0)
    { // fill B

        printf("\tSoc el fill B(%d) de A(%d)\n\tSuma dels dos operands: %d\n", getpid(), getppid(), op1 + op2);

        if ((pide = fork()) == 0)
        { //net E
            printf("\t\tSoc el net E(%d) fill de B(%d)\n\t\tPrimer operand al quadrat: %d\n", getpid(), getppid(), op1 * op1);
            exit(EXIT_SUCCESS);
        }

        sleep(1);

        if ((pidf = fork()) == 0)
        { //net F
            printf("\t\tSoc el net F(%d) fill de B(%d)\n\t\tSegon operand al quadrat: %d\n", getpid(), getppid(), op2 * op2);
            exit(EXIT_SUCCESS);
        }

        sleep(1);

        if ((pidg = fork()) == 0)
        { //net G
            printf("\t\tSoc el net G(%d) fill de B(%d)\n\t\tMitjana dels dos operands: %f\n", getpid(), getppid(), (float)(op1 + op1) / 2.0);
            //enviament del senyal
            kill(pida, SIGUSR1);
            exit(EXIT_SUCCESS);
        }
    }
    else
    { // avi A

        printf("Soc l'avi A(%d) de A(%d)\n\t", getpid(), getppid());
        //Espera la finalització del fill B
        pause(); //waitpid(pidg, &status, 0);
    }
    return 0;
}
