/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 04:55:13 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:23:22 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int			ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	return (ft_strcmp(s1, s2) ? 0 : 1);
}
