/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 21:37:30 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:21:42 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while ((*s1 == *s2) && *s1)
		s1++, s2++;
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
