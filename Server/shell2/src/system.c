

#include "../inc/minishell.h"
#include <sys/stat.h>
#include <dirent.h>


void        execute(char **segment, char *current_dir, char **env)
{
    char *s1;
    char *s2;

    s1 = join(current_dir, "/");
    s2 = join(s1, segment[0]);
    execve(s2, segment, env);
    free(s1);
    free(s2);
}

void        scan_directories(char *pathway, char **segments, char **env)
{
    DIR     *dp;
    struct dirent   *directory;
    char **values;
    int i;
    bool checker;

  
    checker = false;
    values = ft_strsplit(pathway, ':');
    if (!values)
        return ;
    i = 0;
    while (values[i])
    {
        if ((dp = opendir(values[i])) == NULL)
        {
            i++;
            continue ;
        }
        while ((directory = readdir(dp)))
        {
            if (strcmp(directory->d_name, "..") == 0 || strcmp(directory->d_name, ".") == 0)
                continue ;
            if (strcmp(segments[0], directory->d_name) == 0)
            {
                execute(segments, values[i], env);
                checker = true;
                break;    
            }
        }
        if (checker == true)
            break;
        closedir(dp);
        i++;
    }
    if (checker == false)
        putstr("Command not found\n");
    free2d(values);
}

void        scan_path(char **env, char **segments)
{
    int     i;
    char    **key_value;
    char    *pathway;

    i = 0;
    pathway = NULL;
    while (env[i])
    {
        key_value = ft_strsplit(env[i], '=');
        if (strcmp(key_value[0], "PATH") == 0)
        {
            pathway = strdup(key_value[1]);
            free2d(key_value);
            break;
        }
        free2d(key_value);
        i++;
    }
    if (pathway)
    {
        scan_directories(pathway, segments, env);
        free(pathway);
    }
}

void        exec_local_program(char **segments, char **env)
{
    char    *ex;

    ex = strdup(&segments[0][2]);
    free(segments[0]);
    segments[0] = strdup(ex);
    execve(ex, segments, env);
    free(ex);
}

void        ft_system(char **env, char *buffer)
{
    char    **segments;
    pid_t   pid;

    segments = split(buffer, ' ');
    if ((pid = fork()) == 0)
    {
        if (segments[0][0] == '/')
            execve(segments[0], segments, env);
        else if (strncmp(segments[0], "./", 2) == 0)
            exec_local_program(segments, env);
        else 
            scan_path(env, segments);
        exit(1);
    }
    else
        wait(&pid);
    free2d(segments);
}
