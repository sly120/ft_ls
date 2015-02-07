/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/07 15:52:27 by sly               #+#    #+#             */
/*   Updated: 2015/02/07 15:58:48 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>

#include <stdio.h>

void			ft_error_prefix(char *s)
{
	ft_putstr("ls: ");
	perror(s);
}
