#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid1, pid2;
    int status1, status2;

    /* AVI*/
    pid1 = fork();
    if (pid1 == 0)
    { /* PARE */
        if ((pid2 = fork()) == 0)
        { /* NET */
            printf("Soc el NET (%d, fill de %d)\n", getpid(), getppid());
        }
        else
        {
            /* PARE, eperem que el NET acabe, status 0 */
            waitpid(pid2, &status2, 0);
            printf("Soc el PARE (%d, fill de %d)\n", getpid(), getppid());
        }
    }
    else
    { /* AVI */
        /* AVI, esperem que el PARE acabe, status 0*/
        waitpid(pid1, &status1, 0);

        printf("Soc el AVI (%d, fill de %d)\n", getpid(), getppid());
    }

    return 0;
}
