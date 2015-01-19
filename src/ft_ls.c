/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 22:33:03 by sly               #+#    #+#             */
/*   Updated: 2015/01/19 02:11:45 by sly              ###   ########.fr       */
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

static int		ft_addOption(char **options, char c)
{
	char		*s;

	if (!(s = (char*)malloc(sizeof(char) * 2)))
		return (-1);
	s[0] = c;
	s[1] = '\0';
	ft_strcat(*options, s);
	return (0);
}

static int		ft_isOption(char c, char **options)
{
	int			i;

	if ((c == 'a') || (c == 'l') || (c == 'r') || (c == 'R') || (c == 't'))
	{
		i = 0;
		while ((*options)[i])
			if ((*options)[i++] == c)
				return (1);
		if (ft_addOption(options, c) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

static int		ft_readOption(char *arg, char **options)
{
	size_t		i;
	size_t		len;
	int			ret;

	i = 0;
	len = ft_strlen(arg);
	while (++i < len)
	{
		ret = ft_isOption(arg[i], options);
		if (ret == 0)
		{
			if (i == 1 && arg[i] == '-' && arg[i + 1] == '\0')
				return (0);
			ft_errorMessage(arg[i]);
			return (-1);
		}
		else if (ret == -1)
			return (-1);
	}
	return (0);
}

static int		ft_readArg(int argc, char **argv, char **options)
{
	int			i;
	int			ret;

	i = 2;
	while (i <= argc && argv[i - 1][0] == '-')
	{
		ret = ft_readOption(argv[i++ - 1], options);
		if (ret == -1)
			return (-1);
	}
	if (argc - i >= 0)
		ft_putstr("ok\n");
	else
		ft_putstr(".\n");
	return (0);
}

static void		ft_initOptions(char **options)
{
	*options = (char*)malloc(sizeof(char) * (OPTION_NB + 1));
	bzero(*options, OPTION_NB);
}

int				main(int argc, char **argv)
{
	int			ret;
	char		*options;

	ft_initOptions(&options);
	if ((ret = ft_readArg(argc, argv, &options)) == -1)
	{
		ft_putstr("ft_readArg error, abort\n");
		return (1);
	}
	printf("options:%s\n", options);
	//printf("verification options\nl_opt=%d\nR_opt=%d\na_opt=%d\nr_opt=%d\nt_opt=%d\n", options.l_opt, options.R_opt, options.a_opt, options.r_opt, options.t_opt);
	return (0);
}
