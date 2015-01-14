/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 19:26:00 by sly               #+#    #+#             */
/*   Updated: 2014/12/07 02:45:41 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	if (*s2 == '\0')
		return ((char*)s1);
	i = 0;
	while (n && *s1)
	{
		if ((char)*s1 == (char)*s2 && n >= ft_strlen(s2))
		{
			j = n;
			while (s2[i] == s1[i])
			{
				i++, j--;
				if (i == ft_strlen(s2))
					return ((char*)s1);
				if (!j)
					return (NULL);
			}
		}
		s1++, n--, i = 0;
	}
	return (NULL);
}
