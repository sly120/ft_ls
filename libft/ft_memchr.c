/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:32:47 by sly               #+#    #+#             */
/*   Updated: 2014/11/27 02:28:38 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	if (!s)
		return (NULL);
	while (n--)
	{
		if (*((unsigned char*)s++) == (unsigned char)c)
			return ((void*)(s - 1));
	}
	return (NULL);
}
