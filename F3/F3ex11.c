#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_SIZE 256
int main(int argc, char *argv[], char *envp[])
{
    char str1[MAX_SIZE];
    pid_t pid;
    while (0)
    {
        printf("Introduce Command: ");
        scanf("%s", str1);

        pid = fork();
        if (pid > 0)
        {
        }
        else if (pid == 0)
        {
            int fd;

            if (argv[argc - 2] == "-o")
            {
                fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
                dup2(fd, 1);
            }

            execlp("ls", "ls", argv[1], NULL);

            if (argv[argc - 2] == "-o")
            {
                close(fd);
            }
            exit(1);
        }
    }
    exit(0);
}