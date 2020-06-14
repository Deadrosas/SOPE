#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigterm_handler(int signo)
{
    printf("Entering SIGTERM handler ...\n");
    sleep(3);
    printf("Exiting SIGTERM handler ...\n");
}

void sigint_handler(int signo)
{
    printf("Entering SIGINT handler ...\n");
    sleep(10);
    printf("Exiting SIGINT handler ...\n");
}
int main(void)
{
    struct sigaction action, action2;

    action2.sa_handler = sigterm_handler;
    sigemptyset(&action2.sa_mask);
    action.sa_flags = SA_RESTART;
    
    if (sigaction(SIGTERM, &action2, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGTERM handler\n");
        exit(1);
    }

    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action2.sa_flags = 0;
    if (sigaction(SIGINT, &action, NULL) < 0)
    {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Try me with CTRL-C ...\n");
    while (1)
        pause();
    exit(0);
}