/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 11:19:58 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 11:20:01 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <stdbool.h>
#include <ctype.h>

int		count_args(char *str)
{
	bool	whitespace;
	int		count;
	int		i;

	whitespace = false;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (my_isspace(str[i]) && whitespace == false)
		{
			whitespace = true;
			count++;
		}
		if (whitespace == true && !my_isspace(str[i]))
			whitespace = false;
		i++;
	}
	return (count);
}
