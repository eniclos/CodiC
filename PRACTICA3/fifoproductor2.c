#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(){
FILE * fp;
char buffer[500],c;
int nbytes;

fp=fopen("FIFOfile","w");

if (fp==-1){
perror("ERROR OPENING FILE\n");
exit(1);
}

nbytes=0;
//strcmp(buffer,"\0");
printf ("Waiting data to send...\n");
printf("\t Write data: ");

while((c=getchar())!='.'){
	buffer[nbytes++]=c;
	fputc(c,fp);
	//putchar(c);
	printf("\t Write data: ");
}

buffer[nbytes]='\0';


//write (fp,buffer,strlen(buffer));
//printf("eixida %s",buffer);
fclose(fp);
return 0;
}
