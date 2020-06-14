#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static double growthModifier = -1;
static double value = 0;

void signal_handler(int signo)
{
    value+=growthModifier;
    printf("%f\n", value);
}

int main(void)
{

    pid_t sonPid = fork();
    if (sonPid == 0)
    {
        struct sigaction action, action2;

        action2.sa_handler = signal_handler;
        sigemptyset(&action2.sa_mask);
        action.sa_flags = SA_RESTART;

        if (sigaction(SIGUSR1, &action2, NULL) < 0)
        {
            fprintf(stderr, "Unable to install SIGTERM handler\n");
            exit(1);
        }

        action.sa_handler = signal_handler;
        sigemptyset(&action.sa_mask);
        action2.sa_flags = 0;
        if (sigaction(SIGUSR2, &action, NULL) < 0)
        {
            fprintf(stderr, "Unable to install SIGINT handler\n");
            exit(1);
        }

        while(1){
            /*sigemptyset(&action.sa_mask);
            sigemptyset(&action2.sa_mask);*/
            pause();
        }
    }
    else
    {
        srand(time(NULL));   // Initialization, should only be called once.
        for(int i = 0; i < 50; i++)
        {
            sleep(1);
            int r = rand() % 2;
            if(r == 0){
                kill(sonPid,SIGUSR1);
            }else{
                kill(sonPid,SIGUSR2);
            }
        }
        kill(sonPid,SIGTERM);
    }

    exit(0);
}