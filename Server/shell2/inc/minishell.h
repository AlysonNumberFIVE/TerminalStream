


#ifndef _MINISHELL_
#define _MINISHELL_

#include "libft.h"
#include <stdbool.h>
#include "../alylibc/inc/lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>


char    **init(void);

// env.c

void    print_env(char **env);

// minishell.c

void    shell(char **env, char *buffer);
char    *read_line(void);

// unsetenv.c

char    **run_unsetenv(char buffer[], char **env);
char    **ft_unsetenv(char **env, char *to_remove);

// setenv.c

char    **run_setenv(char buffer[], char **env);
char    **ft_setenv(char **env, char *to_add);

// cd.c

char    **ft_cd(char **env, char *buffer);

// exit.c

void    ft_exit(char **env, char *str);

// echo.c

void    ft_echo(char **env, char *buffer);

// utils.c

void        putstr(char *str);
bool        check_for_env(char **env, char *to_find);
char        *get_env_value(char **env, char *to_get);
bool        change_directory(char *path, char *message);
char        **move_to_oldpwd(char **env);

// system.c

void        ft_system(char **env, char *buffer);

#endif
