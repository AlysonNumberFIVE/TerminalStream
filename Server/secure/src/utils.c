

#include "../inc/minishell.h"


char        *create_env(char *key, char *value)
{
    char *tmp;
    char *env;

    tmp = join(key, "=");
    env = join(tmp, value);
    free(tmp);
    return (env);
}

char        **move_to_oldpwd(char **env)
{
    char *curr;
    char *full_variable;
    char current_dir[1024];

    bzero(current_dir, 1024);
    getcwd(current_dir, 1024);
    curr = get_env_value(env, "PWD");
    full_variable = create_env("OLDPWD", curr);
    env = ft_setenv(env, full_variable);
    free(full_variable);
    full_variable = create_env("PWD", current_dir);
    env = ft_setenv(env, full_variable);
    free(full_variable);
    free(curr);
    return (env);
}

bool    change_directory(char *path, char *message)
{
    int     flag;

    flag = chdir(path);
    if (flag != 0)
    {
        putstr(path);
        putstr(message);
        return (false);
    }
    return (true);
}

char        *get_env_value(char **env, char *to_get)
{
    int i;
    char **key_value;
    char *str;

    str = NULL;
    i = 0;
    while (env[i])
    {
        key_value = ft_strsplit(env[i], '=');
        if (strcmp(key_value[0], to_get) == 0)
        {
            str = strdup(key_value[1]);
            free2d(key_value);
            break;
        }
        free2d(key_value);
        i++;
    }
    return (str);
}

bool        check_for_env(char **env, char *to_find)
{
    int i;
    char **key_value;

    i = 0;
    while (env[i])
    {
        key_value = ft_strsplit(env[i], '=');
        if (strcmp(key_value[0], to_find) == 0)
        {
            free2d(key_value);
            return (true);
        }
        free2d(key_value);
        i++;
    }
    return (false);
}

void        putstr(char *str)
{
    int i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}
