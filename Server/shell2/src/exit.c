

#include "../inc/minishell.h"

void    ft_exit(char **env, char *str)
{
    free2d(env);
    free(str);
    printf("Go die then\n");\
    system("leaks minishell");
    exit(1);
}
