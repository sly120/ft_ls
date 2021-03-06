/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 05:11:07 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:30:52 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	register size_t	i;

	if (!s || !(dst = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len && s[start])
		dst[i++] = s[start++];
	dst[i] = '\0';
	return (dst);
}
