#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 3)
    {
        printf("usage: %s dirname outputFile\n", argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0)
        printf("My child is going to execute command \"ls  %s\" and save it in file %s \n",argv[1], argv[2]);

    else if (pid == 0)
    {
        int fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);

        dup2(fd, 1);

        execlp("ls","ls",argv[1], NULL);

        close(fd);

        exit(1);
    }
    exit(0);
}