#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int pipefd[2];
    int childpid, childpid2;
    char *cmd[3] = {"ls", argv[1], NULL};
    char *cmd2[3] = {"grep", ".c", NULL};
    pipe(pipefd);
    if (childpid = fork())
    {
        //parent
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execvp("grep", cmd2);
    }
    else
    {
        //child
        //write
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execvp("ls", cmd);
    }
    return 0;
}