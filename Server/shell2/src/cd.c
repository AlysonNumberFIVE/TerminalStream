


#include "../inc/minishell.h"

char    **tilder_tingz(char **env, char *path)
{
    bool    checker;
    char    *second_half;
    char    *home;
    char    *complete_path;

    checker = check_for_env(env, "HOME");
    if (checker == false)
        putstr("NOne of that shit here. I'm the carry now bitch\n");
    else
    {
        home = get_env_value(env, "HOME");
        second_half = &path[1];
        if (second_half[0] != '\0')
            complete_path = join(home, second_half);
        else
            complete_path = strdup(home);
        change_directory(complete_path, ": Bruv...\n");
        free(complete_path);
        free(home);
        env = move_to_oldpwd(env);
    }
    return (env);
}

char    **to_root(char **env)
{
    char    *home;
    bool    checker;

    home = NULL;
    checker = check_for_env(env, "HOME");
    
    if (checker == false)
        putstr("Error: HOME not set\n");
    else
    {
        home = get_env_value(env, "HOME");
        change_directory(home, ": >> No such file or directory\n");

        free(home);
        env = move_to_oldpwd(env);
    }

    return (env);
}

char    **go_to_oldpwd(char **env)
{
    char    *oldpwd;
    bool    checker;

    checker = check_for_env(env, "OLDPWD");
    if (checker == false)
        putstr("Error: OLDPWD not set\n");
    else
    {
        oldpwd = get_env_value(env, "OLDPWD");
        change_directory(oldpwd, ": >>> No such file or directory\n");
        putstr(oldpwd);
        putstr("\n");
        free(oldpwd);
        env = move_to_oldpwd(env);
    }
    return (env);
}
//  0
// Users/    alysonngonyama/       minishell
// ../                   ../      


char    *back_steps(size_t slash_len, char **path_slashes)
{
    size_t counter;
    char *target;
    size_t i;
    char *tmp;

    target = (char *)malloc(sizeof(char));
    i = 0;
    counter = arraylen(path_slashes);
    counter -= slash_len;
    while (i < counter)
    {
        tmp = join(target, "/");
        free(target);
        target = join(tmp, path_slashes[i]);
        free(tmp); 
        i++;
    }
    return (target);
}

char    **going_backwards(char **env, char *path)
{
    char    **slashes;
    char    *current_path;
    char    **path_slashes;
    size_t  slash_len;
    char     *target;

    slashes = split(path, '/');
    current_path = get_env_value(env, "PWD");
    path_slashes = ft_strsplit(current_path, '/');
    slash_len = arraylen(slashes);
    if (slash_len >= arraylen(path_slashes))
        target = strdup("/");
    else
    {
        target = back_steps(slash_len, path_slashes);
        putstr(target);
        change_directory(target,"Welcome to hell, we've been waiting for you :)\n");
        env = move_to_oldpwd(env);
    }
    free(target);
    free2d(slashes);
    free(current_path);
    free2d(path_slashes);
    return (env);
 }

char    **cd_and_suffer(char **env, char *path)
{
    char *error_msg;

    if (access(path, F_OK) != 0)
        error_msg = strdup(": Permission denied\n");
    else
        error_msg = strdup(": >>>> No such file or directory\n");
    if (change_directory(path, error_msg) == true)
        env = move_to_oldpwd(env);
    free(error_msg);
    return (env);
}

char    **cd(char **env, char **args)
{
    if (arraylen(args) == 1)
        env = to_root(env);
    else if (strcmp(args[1], "-") == 0)
        env = go_to_oldpwd(env);
    else if (strcmp(args[1], "~") == 0 || strncmp(args[1], "~/", 2) == 0)
        env = tilder_tingz(env, args[1]);
    else if (strncmp(args[1], "..", 2) == 0)
        env = going_backwards(env, args[1]);
    else
        env = cd_and_suffer(env,args[1]); 

    return (env);
}

char    **ft_cd(char **env, char *buffer)
{
    char    **args;

    args = split(buffer, ' ');
    env = cd(env, args);
    free2d(args);
    return (env);
}
