/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 03:32:15 by sly               #+#    #+#             */
/*   Updated: 2014/11/19 04:04:29 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmap(char const *s, char (*f)(char))
{
	char			*dst;
	register size_t	i;

	if (!s || !f || !(dst = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		dst[i] = f(s[i]);
		i++;
	}
	return (dst);
}
