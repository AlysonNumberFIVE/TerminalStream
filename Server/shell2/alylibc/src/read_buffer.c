/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:18:49 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 11:18:54 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lib.h"

void		null_buffer(char buffer[])
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			return ;
		}
		i++;
	}
}

void		read_buffer(char buffer[], size_t size)
{
	size_t	val;

	val = read(0, buffer, size);
	buffer[val] = '\0';
	null_buffer(buffer);
}
