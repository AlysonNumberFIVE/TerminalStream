/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:19:31 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 12:35:00 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char		*sub(char *str, size_t start, size_t len)
{
	char	*new;
	size_t	i;

	if (start > ft_strlen(str) - 1)
		return (NULL);
	if (ft_strlen(&str[start]) < len)
		return (NULL);
	new = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		new[i] = str[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
