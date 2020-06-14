#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


void *functionT(void *argc)
{
    int d = *(int *)argc;

    sem_wait(&sem1);
    printf("Starting thread %d.\n", d);
    sleep(2);
    printf("Closing thread %d.\n", d);
    sem_post(&sem1);
    pthread_exit(NULL);
}

int main()
{


    sem_t sem1;
    int a = 1, b = 2, c = 3, status;
    pthread_t t1, t2, t3;

    sem_init(&sem1, 1, 1); // >0 partilha o semaforo entre processos e 0 entre threads

    int childPid, childPid2;

    if ((childPid = fork()) < 0)
    {
        printf("Error!\n");
        exit(1);
    }
    else if (childPid > 0)
    {
        if ((childPid2 = fork()) < 0)
        {
            printf("Error!\n");
            exit(1);
        }
        else if (childPid2 > 0)
        {
            sem_unlink(&sem1);
            sem_close(&sem1);
            waitpid(0, &status, 0);
        }
        else
        {
            sem_wait(&sem1);
            printf("Starting process %d.\n", getpid());
            sleep(2);
            sem_post(&sem1);
            sem_close(&sem1);
            exit(0);
        }
    }
    else
    {
        sem_wait(&sem1);
        printf("Starting process %d.\n", getpid());
        sem_post(&sem1);
        sem_close(&sem1);
    }
    /*
    pthread_create(&t1, NULL, functionT, (void *) &a);
    pthread_create(&t2, NULL, functionT, (void *) &b);
    pthread_create(&t3, NULL, functionT, (void *) &c);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    */

    pthread_exit(0);
}