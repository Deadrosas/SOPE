#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void signal_handler(int signo)
{
    int status = 0;
    pid_t pid = wait(&status);
    printf("Ehehe zombie %u go brr\n",pid);
}

int main(void)
{
    pid_t pid;
    int i, n, status;

    struct sigaction zombieManage;
    zombieManage.sa_handler = signal_handler;
    sigemptyset(&zombieManage.sa_mask);
    zombieManage.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &zombieManage, NULL) < 0)
    {
        exit(1);
    }

    for (i = 1; i <= 10; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("CHILD no. %d (PID=%d) working ... \n", i, getpid());
            sleep(2); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n", i, getpid());
            exit(0);
        }
    }

    sleep(2);
    for (i = 1; i <= 10; i++)
    {
        printf("PARENT: waiting for child no. %d ...\n", i);
    }
    exit(0);
}