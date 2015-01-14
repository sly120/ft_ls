/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 03:58:38 by sly               #+#    #+#             */
/*   Updated: 2014/11/19 04:10:35 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	register size_t	i;

	if (!s || !f || !(dst = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	return (dst);
}
