#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *)threadnum);
    sleep(1);
    pthread_t pthread_self(void);
    printf("Thread id %lu\n", pthread_self());
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
        pthread_join(threads[t],NULL);
    }
    exit(0);
}