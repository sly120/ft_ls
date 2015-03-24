/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 01:17:27 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:38:06 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int			ft_iswhitespace(int c)
{
	return (c == 9 || c == 10 || c == 32);
}

char				*ft_strtrim(char const *s)
{
	char			*dst;
	register size_t	i;
	register size_t	j;

	dst = ft_strnew(0);
	if (!s)
		return (NULL);
	if (!ft_strlen(s))
		return (dst);
	while (ft_iswhitespace(*s) || !*s)
	{
		if (!*s)
			return (dst);
		s++;
	}
	j = 0;
	while (ft_iswhitespace(s[ft_strlen(s) - j - 1]))
		j++;
	if (!(dst = ft_strnew(ft_strlen(s) - j)))
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s) - j)
		dst[i] = s[i];
	return (dst);
}
