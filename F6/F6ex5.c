#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct arg_struct{
    double arg1;
    double arg2;
    double sumres;
    double difres;
    double prodres;
    double quores;
};


struct arg_struct arguments;


void * sumThread(void * arg){
    
    arguments.sumres = arguments.arg1 + arguments.arg2;

    pthread_exit(NULL);
}

void * difThread(void * arg){

    arguments.difres = arguments.arg1-arguments.arg2;
    
    pthread_exit(NULL);
}

void * prodThread(void * arg){

    arguments.prodres = arguments.arg1*arguments.arg2;
    
    pthread_exit(NULL);
}

void * quoThread(void * arg){

    if(arguments.arg2 == 0){
        pthread_exit(NULL);
    }

    arguments.quores = arguments.arg1/arguments.arg2;
    
    pthread_exit(NULL);
}

int main(int argc, char** argv){

    pthread_t t1, t2, t3, t4;

    arguments.arg1 = atoi(argv[1]);
    arguments.arg2 = atoi(argv[2]);

    pthread_create(&t1,NULL,sumThread, (void *) &arguments);
    pthread_join(t1,NULL);

    pthread_create(&t2,NULL,difThread, (void *) &arguments);
    pthread_join(t2,NULL);

    pthread_create(&t3,NULL,prodThread, (void *) &arguments);
    pthread_join(t3,NULL);

    pthread_create(&t4,NULL,quoThread, (void *) &arguments);
    pthread_join(t4,NULL);


    
    printf("sum: %f\n", arguments.sumres);

    printf("dif: %f\n", arguments.difres);

    printf("prod: %f\n", arguments.prodres);

    if(arguments.arg2 == 0){
        printf("Can't divide by 0!\n");
    }else {
        printf("quoc: %f\n", arguments.quores);
    }

    pthread_exit(0);
}