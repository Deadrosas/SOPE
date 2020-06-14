#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 50000

int totalWriteCalls = 50000;

void *thrfunc(void *arg)
{
    int thisThreadTotalCalls = 0;
    int i, k;

    while(totalWriteCalls > 0){
        write(STDOUT_FILENO,(char *)arg,strlen((char*)arg));
        totalWriteCalls--;
        thisThreadTotalCalls++;
    }
    printf("%d\n",thisThreadTotalCalls);
    return NULL;
}
int main(int argc, char* argv[])
{
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, argv[1]);
    pthread_detach(ta);
    pthread_create(&tb, NULL, thrfunc, argv[2]);
    pthread_detach(tb);
    pthread_exit(0);
}