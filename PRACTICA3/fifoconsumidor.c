#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define TAM_BUF 500


int main(void){
int fp;
char buffer[TAM_BUF];
int nbytes;

mknod("FIFOfile",S_IFIFO|0660,0);


	fp=open("FIFOfile",O_RDONLY);
	nbytes=read(fp,buffer,TAM_BUF-1);
	buffer[nbytes]='\0';
	printf("Cadena rebuda: %s \n",buffer);
	close(fp);

return 0;
}
