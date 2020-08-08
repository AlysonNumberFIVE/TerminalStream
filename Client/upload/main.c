



char    **arraydup(char **environ)
{
    char    **new_array;
    size_t  i;

    new_array = (char **)malloc(sizeof(char *) * arraylen(environ));
    while (i < arraylen(environ))
    {
        new_array[i] = strdup(environ[i]);
        i++;
    }
    new_array[i] = NULL;
    return (new_array);
}


void    minishell(char **env)
{
    while (42)
    {
        // read input
        // if input == '\n' or strlen(input) == 0:
        //     conitnue 
        // else if (strcmp(input, 'cd') == 0) 
        //      env = cd(input)
        // else if (strcmp(input, 'env') == 0
        //      print_env(env);
        // else if (strcmp(input, 'setenv') == 0)
        //      env = set_stuff(env)
        // else if (strcmp(input, 'unsetenv') == 0)
        //      env = remove_stuff(env)
        // else if (strcmp(input, 'exit') == 0)
        //      exit_with_zero_leaks(env);
        // else 
        //      scan PATH for system command (ls, pwd, docker?)
    }
}


int main(void)
{
    extern char **environ;
    
    char **local_env = arraydup(environ);
    minishell(local_env)l;
}
