#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    printf("Exemple d'us de execve():\n");
    printf("--------------------------------------\n");

    char *newargv[] = {"ls", "-l", NULL};
    printf("\t Els fitxers al directori son:\n");
    execve("/bin/ls", newargv);

    printf("Acò NO s'executa mai!!\n\n");
}
