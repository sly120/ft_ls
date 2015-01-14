/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:36:01 by sly               #+#    #+#             */
/*   Updated: 2014/11/15 22:15:27 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	char		*chr;

	if (!s)
		return (NULL);
	chr = (char*)s + ft_strlen(s);
	while (*chr != (char)c)
	{
		if (chr == s)
			return (NULL);
		chr--;
	}
	return (chr);
}
