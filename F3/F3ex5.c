#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(void){

    /*if(fork()>0){
        write(STDOUT_FILENO,"Hello ",6);
    }else{
        write(STDOUT_FILENO, "World!\n",7);
    }*/
    int returnStatus;

    pid_t child_pid = fork();

    if(child_pid==0){
        write(STDOUT_FILENO,"Hello ",6);
        kill(getpid(),SIGTERM);
    }

    child_pid = fork();

    if(child_pid ==0 ){
        write(STDOUT_FILENO,"my ",3);
        kill(getpid(),SIGTERM);
    }

    waitpid(child_pid, &returnStatus, 0);
    write(STDOUT_FILENO, "friends!\n",9);
    return 0;
}