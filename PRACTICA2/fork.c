#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        /* fill */
        printf("Soc el fill (%d) de (%d)\n", getpid(), getppid());
    }
    else
    {
        /* pare */
        printf("Soc el pare (%d) de (%d)\n", getpid(), getppid());
    }
    return 0;
}