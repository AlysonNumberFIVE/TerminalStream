/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraypush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:17:11 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 12:40:09 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "lib.h"

char		**arraypush(char **array, char *str)
{
	char	**newarr;
	size_t	i;

	i = 0;
	if (array == NULL)
	{
		newarr = (char**)malloc(sizeof(char*) * 2);
		newarr[0] = ft_strdup(str);
		newarr[1] = NULL;
	}
	else
	{
		newarr = (char **)malloc(sizeof(char*) * (arraylen(array) + 2));
		while (array[i])
		{
			newarr[i] = ft_strdup(array[i]);
			i++;
		}
		newarr[i] = ft_strdup(str);
		newarr[++i] = NULL;
		free2d(array);
	}
	return (newarr);
}
