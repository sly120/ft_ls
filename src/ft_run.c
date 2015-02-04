/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:26:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/04 16:29:49 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>

static int				ft_getStat(char *path, struct stat **buf)
{
	int					ret;

	*buf = (struct stat*)malloc(sizeof(struct stat));
	if ((ret = stat(path, *buf) == -1))
		return (-1);
	//printf("mode of %s:%d\n", path, (*buf)->st_mode);
	return (0);
}

/*static int				ft_openDir(char *path)
{
	DIR					*stream;
	struct dirent		*dirent;
	int					ret;

	if (!(stream = opendir(path)))
		return (-1);
	while ((dirent = readdir(stream)))
		ft_putendl(dirent->d_name);
	if ((ret = closedir(stream)) == -1)
		return (-1);
	return (0);
}*/

/*static int			ft_recursiveRun(char *path)
  {
  }
  */

static void				ft_dirAdd(t_dir **dirLst, t_dir *newDir)
{
	t_dir				*csr;

	if (!dirLst || !newDir)
		return ;
	if (!*dirLst)
		*dirLst = newDir;
	else
	{
		csr = *dirLst;
		while (csr->next)
			csr = csr->next;
		csr->next = newDir;
	}
}

static t_dir			*ft_dirnew(int d_mode, char *d_name)
{
	t_dir				*tmp;
	size_t				len;

	if (!(tmp = (t_dir*)malloc(sizeof(t_dir))))
		return (NULL);
	len = ft_strlen(d_name);
	if (!(tmp->name = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(tmp->name, d_name, len);
	(tmp->name)[len] = '\0';
	tmp->mode = d_mode;
	tmp->next = NULL;
	return (tmp);
}

void					ft_run(int argc, char **argv, int i, char *options)
{
	/*
	 *	dirLst[0]: list of operands which are not a file nor a directory
	 *	dirLst[1]: list of files and directories
	 *	temp[0]: count
	 *	temp[1]: isdirLst[0]
	 *	temp[2]: isdirLst[1]
	 */
	t_dir				*dirLst[2];
	int					temp[3];
	struct stat			*dirRaw;
	//t_dir				*check;

	temp[0] = 0;
	temp[1] = 0;
	temp[2] = 0;
	while (temp[0] < 2)
		dirLst[(temp[0])++] = NULL;
	temp[0] = i;
	if (argc >= temp[0])
		while (temp[0] <= argc)
		{
			if (ft_getStat(argv[temp[0] - 1], &dirRaw) == -1)
			{
				printf("fail to open:%s, errno:%d, temp[0]:%d, i:%d\n", argv[temp[0] - 1], errno, temp[0], i);
				ft_dirAdd(&dirLst[0], ft_dirnew(-1, argv[temp[0] - 1]));
				temp[1] = 1;
			}
			else
			{
				//printf("argv:%s\n", argv[temp[0] - 2]);
				ft_dirAdd(&dirLst[1], ft_dirnew(dirRaw->st_mode, argv[temp[0] - 1]));
				//int i = ((dirLst[1]->mode) & (1 << 14)) > 0;
				printf("Directory test:%d, mode value:%d, operand name:%s, temp[0]:%d, i:%d\n", temp[0] - 1, dirLst[1]->mode, dirLst[1]->name, temp[0], i);
				temp[2] = 1;
			}
			temp[0]++;
				//printf("Directory test:%d, mode value:%d,  operand name:%s\n", temp[0] - 2, dirLst[1]->next->mode, dirLst[1]->next->name);
		}
	else
	{
		ft_putendl(".");
		//ft_getStat(".", &dirRaw);
	}
	if (temp[1] == 1)
	{
		/*check = dirLst[0];
		while (check)
		{
			printf("check: %s\n", check->name);
			check = check->next;
		}*/
		ft_sort(&dirLst[0]);
		free(dirLst[0]);
	}
	if (temp[2] == 1)
	{
		ft_sort(&dirLst[1]);
		free(dirLst[1]);
	}
	while (*options)
		options++;
}
