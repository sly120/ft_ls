/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 20:06:15 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:22:06 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char				*ft_strcpy(char *dst, const char *src)
{
	register int	i;

	if (!src)
		return (dst);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
