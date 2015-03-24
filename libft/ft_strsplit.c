/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 23:08:12 by sly               #+#    #+#             */
/*   Updated: 2015/02/07 19:35:26 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t			ft_subslen(char const *s, char c)
{
	register char		*str;

	str = (char*)s;
	while (*str != c && *str != '\0')
		str++;
	return ((size_t)(str - s));
}

static char				*ft_subsdup(char *src, char c)
{
	char				*dst;
	register int		i;

	dst = ft_strnew(ft_subslen(src, c));
	i = -1;
	while (src[++i] && src[i] != c)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

static int				ft_switchcount(char const *s, char c)
{
	register int		i;
	register int		j;
	register int		res;

	i = 0;
	j = -1;
	while (s[++j])
	{
		if (s[j] == c && s[j + 1] != c && s[j + 1] != '\0')
			i++;
		if (s[j] != c && s[j + 1] == c && s[j + 1] != '\0')
			i++;
	}
	res = 0;
	if (*s == c)
		res = i / 2 + i % 2;
	else
		res = i / 2 + 1;
	return (res);
}

char					**ft_strsplit(char const *s, char c)
{
	char				**stab;
	char				*str;
	register int		subs;
	register int		i;

	if (!s)
	{
		stab = (char**)ft_memalloc(sizeof(char*));
		stab[0] = NULL;
		return (stab);
	}
	subs = ft_switchcount(s, c);
	if (!(stab = (char**)malloc((subs + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	str = (char*)s;
	while (*str && i < subs)
	{
		while (*str == c)
			str++;
		stab[i++] = ft_subsdup(str, c);
		str = str + ft_subslen(str, c);
	}
	stab[i] = NULL;
	return (stab);
}
