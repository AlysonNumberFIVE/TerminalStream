/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:19:02 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 12:35:11 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char		**arraypush_and_null(char **array, char **s)
{
	array = arraypush(array, *s);
	free_and_null(s);
	return (array);
}

char		**split(char *str, char delim)
{
	char		**array;
	char		*s;
	int			i;

	i = -1;
	array = NULL;
	s = NULL;
	while (str[++i])
		if (str[i] == delim)
		{
			if (ft_strlen(s) == 0)
				continue ;
			else
				array = arraypush_and_null(array, &s);
		}
		else
			s = charpush(s, str[i]);
	if (s)
		array = arraypush_and_null(array, &s);
	return (array);
}
