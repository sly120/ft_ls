/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 06:00:20 by sly               #+#    #+#             */
/*   Updated: 2015/01/20 06:32:56 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

static int				ft_openTestDir(char *path)
{
	struct stat			*buf;
	int					ret;

	buf = (struct stat*)malloc(sizeof(struct stat));
	if ((ret = stat(path, buf) == -1))
		return (-1);
	printf("mode of %s:%d\n", path, buf->st_mode);
	return (0);
}

/*static int			ft_openDir(char *path)
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
*/

static int			ft_recursiveRun(char *path)
{
}

void				ft_run(int argc, char **argv, int i, char *options)
{
	int				temp;

	temp = i;
	if (argc >= temp)
		while (argc >= temp)
		{
			if (ft_openTestDir(argv[temp++ - 1]) == -1)
				ft_errorNonDirectoryOperand(argv[temp - 2]);
		}
	else
	{
		printf("i:%d et argc:%d\n", i, argc);
		ft_putendl(".");
		ft_openTestDir(".");
	}
	while (*options)
		options++;
}
