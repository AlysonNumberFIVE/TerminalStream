/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:22:25 by angonyam          #+#    #+#             */
/*   Updated: 2017/05/28 22:45:38 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		length;
	int		i;
	char	*s2;

	length = 0;
	while (s1[length] != '\0')
		length++;
	length++;
	s2 = (char *)malloc(sizeof(char) * length);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
