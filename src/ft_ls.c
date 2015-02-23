/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 22:33:03 by sly               #+#    #+#             */
/*   Updated: 2015/02/23 22:18:05 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

#include <stdio.h>

int				main(int argc, char **argv)
{
	char		*options;
	int			ret;

	if (!(options = (char*)malloc(sizeof(char) * (OPTION_NB + 1))))
		return (-1);
	ft_bzero(options, OPTION_NB);
	ret = ft_readArg(argc, argv, &options);
	ft_sort_charTab(&argv, argc, ret);
	/*ret = 0;
	while (argv[ret])
		ft_putendl(argv[ret++]);
	*/ret = ft_run(argc, argv, ret, options);
	ft_putstr("hehe\n");
	if (ret == -1)
		return (-1);
	free(options);
	ft_putstr("haha\n");
	return (0);
}
