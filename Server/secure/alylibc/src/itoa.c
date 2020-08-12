/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:17:34 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 11:18:23 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int			number_len(int value)
{
	int		size;

	size = 0;
	while (value > 0)
	{
		value /= 10;
		size++;
	}
	return (size);
}

char		*itoa(int value)
{
	int		size;
	char	*number;

	size = number_len(value);
	number = (char*)malloc(sizeof(char) * size + 1);
	number[size--] = '\0';
	while (value > 0)
	{
		number[size] = value % 10 + '0';
		size--;
		value /= 10;
	}
	return (number);
}
