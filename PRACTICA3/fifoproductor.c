#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(){
int fp,i;
char buffer[500];

fp=open("FIFOfile",O_WRONLY);

if (fp==-1){
perror("ERROR OPENING FILE\n");
exit(1);
}

//strcmp(buffer,"\0");
printf ("Waiting data to send...\n");
printf("\t Write data: ");


scanf("%[^\n]s",&buffer);

for(i=0;i<strlen(buffer);i++){
	if(buffer[i]=='.') //write on pipe
		buffer[i]='\0';
}

write (fp,buffer,strlen(buffer));
//printf("eixida %s",buffer);
close(fp);
return 0;
}
