/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 12:59:37 by sly               #+#    #+#             */
/*   Updated: 2014/11/25 01:23:32 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		ft_memcpy(dst, src, 1);
		if (*((unsigned char*)src) == (unsigned char)c)
			return ((void*)dst + 1);
		dst++, src++;
	}
	return (NULL);
}
