#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *nome = argv[1];
    int times = atoi(argv[2]);
    for (int i = 0; i < times; ++i)
    {
        printf("Hello %s!\n", nome);
    }
    return argc;
}