/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 22:33:03 by sly               #+#    #+#             */
/*   Updated: 2015/01/18 05:26:23 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>
#include <stdio.h>

static void		ft_errorMessage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-Ralrt] [file ...]\n", 2);
}

static int		ft_isOption(char c)
{
	return ((c == 'a') || (c == 'l') || (c == 'r') || (c == 'R') || (c == 't'));
}

static int		ft_readOption(char *arg)
{
	size_t		i;
	size_t		len;
	int			ret;

	i = 0;
	len = ft_strlen(arg);
	while (++i < len)
	{
		ret = ft_isOption(arg[i]);
		if (ret == 0)
		{
			if (i == 1 && arg[i] == '-' && arg[i + 1] == '\0')
				return (0);
			ft_errorMessage(arg[i]);
			return (-1);
		}
	}
	return (0);
}

static int		ft_readArg(int argc, char **argv)
{
	int			i;
	int			ret;

	i = 2;
	while (i <= argc && argv[i - 1][0] == '-')
	{
		ret = ft_readOption(argv[i++ - 1]);
		if (ret == -1)
			return (-1);
	}
	if (argc - i > 0)
		ft_putstr("ok\n");
	else
		ft_putstr(".\n");
	return (0);
}

int				main(int argc, char **argv)
{
	int			ret;

	ret = ft_readArg(argc, argv);
	if (ret == -1)
		return (1);
	return (0);
}
