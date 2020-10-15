#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define TAM_BUF 500


int main(void){
FILE * fp;
char buffer[TAM_BUF],c;
int nbytes, i;

mknod("FIFOfile",S_IFIFO|0660,0);
nbytes=0;

fp=fopen("FIFOfile","r");
 while((c = fgetc(fp)) != EOF) {
		if(c != '.')
		buffer[nbytes++]=c;
	}

	buffer[nbytes]='\0';
	printf("Cadena rebuda: %s \n",buffer);
	fclose(fp);

return 0;
}
