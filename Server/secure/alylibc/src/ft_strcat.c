/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:51:47 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 10:39:05 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lib.h"
#include <string.h>

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int count;

	i = 0;
	count = (ft_strlen(s1));
	while (s2[i])
	{
		s1[count + i] = s2[i];
		i++;
	}
	s1[count + i] = '\0';
	return (s1);
}
