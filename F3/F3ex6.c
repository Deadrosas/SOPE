#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
    pid_t pid;
    int i, j, status;
    printf("I'm process %d. My parent is %d.\n", getpid(), getppid());
    for (i = 1; i <= 3; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            printf("fork error");
            exit(1);
        }
        else if (pid == 0)
        {
            pid_t cpid = getpid();
            pid_t ppid = getppid();
            printf("I'm process %d. My parent is %d. I'm going to work for 1 second ...\n", cpid, ppid);
            sleep(1); // simulando o trabalho do filho
            printf("I'm process %d. My parent is %d. I finished my work\n", cpid,ppid);
            kill(getpid(),SIGKILL);
            //exit(0);
        }
        else // simulando o trabalho do pai
            for (j = 1; j <= 10; j++)
            {
                sleep(1);
                if(waitpid(pid,&status,0));
                printf("father working ...\n");
            }
    }
    exit(0);
}