
#include "../inc/minishell.h"


void    normalie_normalie(char buffer[])
{
    int i;

    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\t')
            buffer[i] = ' ';
        i++;
    }
}

char    *read_line(void)
{
    size_t size;
    char *str;
    char buffer[4096];

    bzero(buffer, 4096);
    size = read(0, buffer, 4096);
    if (size >= 4096)
        buffer[4095] = '\0';
    buffer[size - 1] = '\0'; 
    normalie_normalie(buffer);
    str = strtrim(buffer);
    return (str); 
}

void    shell(char **env, char *buffer)
{
        if (strncmp(buffer, "unsetenv ", 9) == 0)
            env = run_unsetenv(buffer, env); 
        else if (strncmp(buffer, "env ", 3) == 0)
            print_env(env);
        else if (strncmp(buffer, "setenv ", 7) == 0)
            env = run_setenv(buffer, env);
        else if (strncmp(buffer, "exit ", 4) == 0)
            ft_exit(env, buffer);
        else if (strncmp(buffer, "echo ", 5) == 0 || strcmp(buffer, "echo") == 0)
            ft_echo(env, buffer);
        else if (strncmp(buffer, "cd ", 3) == 0 || strcmp(buffer, "cd") == 0)
            env = ft_cd(env, buffer);
        else
            ft_system(env, buffer);
}




