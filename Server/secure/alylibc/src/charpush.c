/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charpush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:17:15 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 11:20:58 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <string.h>
#include <stdlib.h>

char	*charpush(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	if (str == NULL)
	{
		new = (char*)malloc(sizeof(char) * 2);
		new[0] = c;
		new[1] = '\0';
	}
	else
	{
		new = (char*)malloc(sizeof(char) * ft_strlen(str) + 2);
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
		new[i] = c;
		new[++i] = '\0';
		free(str);
	}
	return (new);
}
