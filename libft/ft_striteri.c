/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 03:03:44 by sly               #+#    #+#             */
/*   Updated: 2014/11/19 03:28:59 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char		*sinit;

	if (s && f)
	{
		sinit = s;
		while (*s)
		{
			f((unsigned int)(s - sinit), s);
			s++;
		}
	}
}
