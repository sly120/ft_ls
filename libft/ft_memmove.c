/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 18:19:47 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:16:07 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!src)
		return (dst);
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
		while (len--)
			(*((char*)dst + len)) = (*((char*)src + len));
	return (dst);
}
