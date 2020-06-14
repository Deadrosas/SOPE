#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
    /*char substring[5];
  for (char **env = envp; *env != 0; env++)
  {
    char *thisEnv = *env;
    if(strncmp(thisEnv,"USER=",5) == 0){
        memcpy(substring,&thisEnv[5],4);
        substring[4] = '\0';
        printf("Hello %s!\n",substring);
        return 0;
    }
  }*/

    printf("Hello %s!\n", getenv("USER_NAME"));
    return 0;
}