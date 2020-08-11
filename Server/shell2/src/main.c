



#include "../alylibc/inc/lib.h"
#include "../inc/minishell.h"
#include <signal.h>


char    **init(void)
{
    extern char **environ;
    char    **env;
    int    counter;

    env = NULL;
    counter = 0;
    while (environ[counter])
    {
        env = arraypush(env, environ[counter]);
        counter++;
    }
    return (env);
}

