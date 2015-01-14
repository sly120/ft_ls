/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 02:28:58 by sly               #+#    #+#             */
/*   Updated: 2014/11/25 00:54:33 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intcount(int n, int i)
{
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			neg;
	int			i;
	char		*s;

	i = 1;
	neg = 1;
	if (n >= 0)
	{
		i = 0;
		n = -n;
		neg = 0;
	}
	i = ft_intcount(n, i);
	if (!(s = ft_strnew(i + neg)))
		return (NULL);
	s[0] = '-';
	if (n == 0)
		s[0] = '0';
	while (n != 0)
	{
		s[--i] = '0' - n % 10;
		n /= 10;
	}
	return (s);
}
