/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:18:38 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 11:18:46 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char		*normalize_string(char *str)
{
	size_t	i;
	char	*new;

	new = ft_strdup(str);
	i = 0;
	while (new[i])
	{
		if (new[i] == '\t')
			new[i] = ' ';
		i++;
	}
	return (new);
}
