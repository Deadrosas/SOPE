#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int fd[2];

char numeros[3*sizeof(char)][2] , numberArray[3*sizeof(char)][2];

void waitingParent(int signo){
    close(fd[1]);
    read(fd[0], numeros[0], 3*sizeof(char));
    read(fd[0], numeros[1], 3*sizeof(char));

    printf("Sum: %d+%d=%d\n", atoi(numeros[0]), atoi(numeros[1]), atoi(numeros[0]) + atoi(numeros[1]));
    printf("Diference: %d-%d=%d\n", atoi(numeros[0]), atoi(numeros[1]), atoi(numeros[0]) - atoi(numeros[1]));
    printf("Product: %d*%d=%d\n", atoi(numeros[0]), atoi(numeros[1]), atoi(numeros[0]) * atoi(numeros[1]));
    if( atoi(numeros[1])!=0 ){
        printf("Quociente: %d/%d=%d\n", atoi(numeros[0]), atoi(numeros[1]), atoi(numeros[0]) / atoi(numeros[1]));
    }
    else{
        printf("Can't divide by zero\n");
    }

}


int main(){

    struct sigaction handler;
    handler.sa_handler = waitingParent;
    sigemptyset(&handler.sa_mask);
    handler.sa_flags = 0;


    pid_t childPid;

    if(pipe(fd)<0){
        printf("Error creating pipe\n");
        exit(1);
    }

    if( (childPid = fork()) < 0){
        printf("Error forking\n");
        exit(2);
    }
    else if(childPid>0){ //Parent
        close(fd[0]);
        printf("Introduce next number:\n");
        scanf("%s",numberArray[0]);
        printf("Introduce next number:\n");
        scanf("%s",numberArray[1]);
        write(fd[1], numberArray[0] , 3*sizeof(char));
        write(fd[1], numberArray[1] , 3*sizeof(char));
        kill(childPid,SIGUSR1);
        exit(0);
    }
    else{ //Child

        if(sigaction(SIGUSR1,&handler, NULL) < 0){
            printf("Unable to install handler\n");
            exit(3);
        }

        pause();

        exit(0);

    }



}