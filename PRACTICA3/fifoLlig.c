#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAM_BUF 500
#define TRUE 1

int main()
{
	int fp;
	char buffer[TAM_BUF];
	int nbytes;

	mknod("FIFO1", S_IFIFO | 0660, 0);

	while (TRUE)
	{
		fp = open("FIFO1", O_RDONLY);
		nbytes = read(fp, buffer, TAM_BUF - 1);
		buffer[nbytes] = '\0';
		printf("Cadena rebuda: %s \n", buffer);
		close(fp);
	}
	return 0;
}
