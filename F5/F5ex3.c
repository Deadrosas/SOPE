#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int fd[2];

    char* buffer[256];
    int file_fd = open(argv[1], O_RDWR | O_CREAT, 0644);

    //dup2(,STDOUT_FILENO);

    int childPid = fork();
    if(childPid < 0){
        printf("Error.\n");
        exit(1);
    }else if(childPid == 0){
        close(fd[1]);
        //while()
        read(fd[0],&buffer,256);

    }

    
    while(1){

    }
    write(1,&buffer,256);

    









    exit(0);
}