#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    pid_t pidAB, pidBE, pidBG, pidBF, pidAC, pidAD;
    int status1, status2;

    /* A */
    pidAB=fork();
    if ( pidAB== 0 ){ /* B*/



        if ( (pidBE=fork()) == 0 ){ /* E */
            printf("Soc E (%d, fill de %d)\n",getpid(), getppid());
        }else{

            if ( (pidBF=fork()) == 0 ){ /* F */
                waitpid(pidBE, &status1, 0);
                printf("Soc F (%d, fill de %d)\n",getpid(), getppid());
            }else{

                if ( (pidBG=fork()) == 0 ){ /* G */
                    waitpid(pidBF, &status1, 0);
                    printf("Soc G (%d, fill de %d)\n",getpid(), getppid());
                }//endif
            }//endelse
        }//endelse

    /* B */
       waitpid(pidBG, &status2, 0);
       printf("Soc B (%d, fill de %d)\n",  getpid(), getppid());
    }else{
        /* A */
        waitpid(pidAB, &status1, 0);

        if ( (pidAC=fork()) == 0 ){ /* C */
            //waitpid(pidBG, &status1, 0);
            printf("Soc el C (%d, fill de %d)\n",getpid(), getppid());

        }else{ if ( (pidAD=fork()) == 0 ){ /* D */
                    waitpid(pidAC, &status1, 0);
                    printf("Soc el D (%d, fill de %d)\n",getpid(), getppid());

                }//endif
         }//endelse
         /* A */

         printf("Soc el A (%d, fill de %d)\n",getpid(), getppid());
    }//endelse

return 0;
}
