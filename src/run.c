/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 06:00:20 by sly               #+#    #+#             */
/*   Updated: 2015/01/19 06:39:07 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <libft.h>

static int			ft_openDir(char *path)
{
	DIR				*stream;
	struct dirent	*dirent;
	int				ret;

	if (!(stream = opendir(path)))
		return (-1);
	while ((dirent = readdir(stream)))
		ft_putendl(dirent->d_name);
	if ((ret = closedir(stream)) == -1)
		return (-1);
	return (0);
}

void				ft_run(int argc, char **argv, int i, char *options)
{
	if (argc >= i)
		while (argc >= i)
		{
			if (ft_openDir(argv[i++ - 1]) == -1)
			{
				ft_putstr(argv[i - 2]);
				ft_putendl(" error ft_openDir");
			}
		}
	else
	{
		ft_putendl(".");
		ft_openDir(".");
	}
	while (*options)
		options++;
}
