#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid1;

    //Variable INCIAL
    int variable = 6;

    pid1 = fork();
    if (pid1 == 0)
    { /* fill */
        printf("Soc el FILL (%d). %d - 5 = %d\n", getpid(), variable, variable - 5);
    }
    else
    { /* pare */

        printf("Soc el PARE (%d). %d + 5 = %d\n", getpid(), variable, variable + 5);
    }

    return 0;
} 