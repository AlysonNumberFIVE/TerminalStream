



#include "../alylibc/inc/lib.h"
#include "../inc/minishell.h"
#include <signal.h>


char    **init(void)
{
    extern char **environ;
    char    **env;
    int    counter;
    char    currdir[1024];

    bzero(currdir, 1024);
    getcwd(currdir, 1024);
    env = NULL;
    counter = 0;
    while (environ[counter])
    {
        env = arraypush(env, environ[counter]);
        counter++;
    }
//    ev = arraypush(env, currdir);
    return (env);
}

