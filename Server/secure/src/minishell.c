
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

void    ft_pwd(char root[])
{
    char currpath[1024];

    bzero(currpath, 1024);
    getcwd(currpath, 1024);
    if (strlen(currpath) == strlen(root))
        printf("/\n");
    else
        printf("%s\n", &currpath[strlen(root)]); 
}


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

char    *going_backwards(char *path)
{
    char    **slashes;
    char    *current_path;
    char    **path_slashes;
    size_t  slash_len;
    char     *target;
    extern char root[1024];
    char currpath[1024];


    bzero(currpath, 1024);
    getcwd(currpath, 1024);
    slashes = split(path, '/');
    current_path = strdup(currpath);
    path_slashes = ft_strsplit(current_path, '/');
    slash_len = arraylen(slashes);
    if (slash_len >= arraylen(path_slashes))
        target = strdup("/");
    else
    {
        target = back_steps(slash_len, path_slashes);
        printf("%s\n", target);
    }
    free2d(slashes);
    free(current_path);
    free2d(path_slashes);
    return (target);
 }
void    ft_cd(char *buffer)
{
    char **args;
    char *target;
    extern char root[1024];

    target = NULL;
    args = split(buffer, ' ');
    if (args[1])
    {
        if (strcmp(args[1], "/") == 0 || strcmp(args[1], "~") == 0)
            target = strdup(root);
        else if (strncmp("../", args[1], 3) == 0 || strcmp("..", args[1]) == 0)
        {
            target = going_backwards(args[1]);
            if (strlen(target) < strlen(root))
            {
                free(target);
                target = strdup(root);
            }
        }
        else 
        {
            target = strdup(args[1]);
            //chdir(target);
        }
    /*    if (chdir(target) != 0)
            printf("cd : Directory doesn't exist\n");
        else
        {
            printf("changed to %s\n",target);
            free(target);
        } */
    }
    else
    {
        chdir(root);
        printf("changed to %s\n", root);
    }
}

void    shell(char **env, char *buffer)
{
    extern char root[1024];
        if (buffer[0] == '/')
            printf("forbidden\n");
        else if (strncmp(buffer, "cd ", 3) == 0 || strcmp(buffer, "cd") == 0)
        {
            printf("cd disabled : visit project Github page for details on code.\n");
        }
        else if (strcmp(buffer, "pwd") == 0)
            ft_pwd(root);
        else
        {
            ft_system(env, buffer); 
        }
}




