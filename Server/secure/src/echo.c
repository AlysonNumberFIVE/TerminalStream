
#include "../inc/minishell.h"

void        print_env_var(char **env, char *to_print)
{
    int i;
    char **key_value;

    i = 0;
    while (env[i])
    {
        key_value = ft_strsplit(env[i], '=');
        if (strcmp(key_value[0], to_print) == 0)
        {
            putstr(key_value[1]);
            free2d(key_value);
            break;
        }
        free2d(key_value);
        i++;
    }
}

char        **get_next_next_lines(char type)
{
    char    *str;
    char    **array;

    array = NULL;
    while (42)
    {
        write(1, ">", 1);
        str = read_line();
        if (strchr(str, type))
        {
            array = arraypush(array, str);
            free(str);
            break;
        }
        array = arraypush(array, str);
        free(str);
    }
    return (array);
}




char       **validate_subshell(char **segments, char **exp)
{
    int i;
    char *type;
    char **extra_lines;

    extra_lines = NULL;
    type = NULL;
    i = 0;
    while (segments[i])
    {
        if ((type = strchr(segments[i], '\'')) || (type = strchr(segments[i], '\"')))
           break ;
        i++; 
    }
    if (type)
    {
        extra_lines = get_next_next_lines(type[0]);
    }
    *exp = type;
    return (extra_lines);
}

void        leave_the_ticks(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            i++;
            continue ;
        }
        write(1, &str[i], 1);
        i++;
    }
}

void        print_subshell(char **subshell, char *exp)
{
    int i;

    i = 0;
    while (subshell[i])
    {
        leave_the_ticks(subshell[i], exp[0]);
        putstr("\n");
        i++;
    }
    free(exp);
    free2d(subshell);
}

void        print_stuff(char **env, char **segments)
{
    int     i;
    char    **subshell;
    char    *exp;

    exp = NULL;
    subshell = validate_subshell(segments, &exp);
    i = 1;
    while (segments[i])
    {
        if (segments[i][0] == '$')
            print_env_var(env, &segments[i][1]);
        else
            leave_the_ticks(segments[i], exp[0]);
         //   putstr(segments[i]);
        if (segments[i + 1] != NULL)
            putstr(" "); 
        i++;
    }
    putstr("\n");
    if (subshell)
        print_subshell(subshell, exp);

}

void        ft_echo(char **env, char *buffer)
{
    char **args;

    args =ft_strsplit(buffer, ' ');
    print_stuff(env, args);
    free2d(args);
}
