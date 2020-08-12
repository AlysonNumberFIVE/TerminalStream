


#include "../inc/minishell.h"


void    print_env(char **env)
{
    int counter;

    counter = 0;
    while (env[counter])
    {
        printf("%s\n", env[counter]);
        counter++;
    }
}
