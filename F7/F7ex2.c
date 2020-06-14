#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define STDERR 2
#define NUMITER 10000

int total_output = NUMITER;
int total_written = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *thrfunc(void *arg)
{
    int i;

    fprintf(stderr, "Starting thread %s\n", (char *)arg);

    while(total_output>1){
        pthread_mutex_lock(&mut);
        write(STDERR, arg, 1);
        total_output--;
        total_written++;
        pthread_mutex_unlock(&mut);

    }
    return NULL;
}
int main()
{
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    printf("\n%d\n",total_written);
    return 0;
}