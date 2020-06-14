#include <stdio.h>
#include <stdlib.h>
#define BUF_LENGTH 256
#define MAX 256
int main(int argc, char** argv)
{
    if(argc!=3){
        printf("usage: nome_do_executavel file1 file2\n");
        exit(3);
    }
    FILE *src, *dst;
    char buf[BUF_LENGTH];
    if ((src = fopen(argv[1], "r")) == NULL)
    {
        perror("Error:");
        exit(1);
    }
    if ((dst = fopen(argv[2], "w")) == NULL)
    {
        perror("Error:");
        exit(2);
    }
    while ((fgets(buf, MAX, src)) != NULL)
    {
        fputs(buf, dst);
    }
    fclose(src);
    fclose(dst);
    exit(0); // zero é geralmente indicativo de "sucesso"
}