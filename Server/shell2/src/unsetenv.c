


#include "../inc/minishell.h"

char   **run_unsetenv(char buffer[], char **env)
{
    char    **args;

    args = split(buffer, ' '); 
    if (arraylen(args) == 2)
        env = ft_unsetenv(env, args[1]);
    else
        printf("Error: You suck at this\nUsage: unsetenv [ENV TO REMOVE\n]");
    free2d(args);
    return (env);
}

char    **ft_unsetenv(char **env, char *to_remove)
{
    int     counter;
    char    **tmp;
    bool    checker;
    char    **key_value;

    checker = false;
    tmp = NULL;
    counter = 0;
    while (env[counter])
    {
        key_value = split(env[counter], '=');
        if (strcmp(key_value[0], to_remove) == 0)
        {
            checker = true;
            counter++;
            free2d(key_value);
            continue;
        }
        free2d(key_value);
        tmp = arraypush(tmp, env[counter]);
        counter++;
    }
 
    if (checker == false)
        printf("Error: no such env found\n");
    free2d(env);
    env = tmp;
    return (env);
}

