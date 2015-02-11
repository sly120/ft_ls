/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:26:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/11 21:21:39 by sly              ###   ########.fr       */
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

void					ft_discriminate_dir(t_dir **dirLst[3], struct stat *raw,
											int i, char **argv)
{
}

int						ft_run(int argc, char **argv, int i, char *options)
{
	/*
	 *	dirLst[0]: list of operands which are not a file nor a directory
	 *	dirLst[1]: list of files
	 *	dirLst[1]: list of directories
	 *	tab[0]: count
	 *	tab[1]: isdirLst[0] indicator
	 *	tab[2]: isdirLst[1] indicator
	 *	tab[3]: isdirLst[2] indicator
	 */
	t_dir				*dirLst[3];
	int					tab[4];
	struct stat			*dirRaw;
	t_dir				*check;

	if (i == -1)
		return (-1);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	while (tab[0] < 3)
		dirLst[(tab[0])++] = NULL;
	tab[0] = i;
	if (argc >= tab[0])
		while (tab[0] <= argc)
		{
			if (ft_getStat(argv[tab[0] - 1], &dirRaw) == -1)
			{
				//printf("fail to open:%s, errno:%d, tab[0]:%d, i:%d\n", argv[tab[0] - 1], errno, tab[0], i);
				ft_dirAdd(&dirLst[0], ft_dirnew(-1, argv[tab[0] - 1]));
				tab[1] = 1;
			}
			else
			{
				//printf("argv:%s\n", argv[tab[0] - 2]);
				if (dirRaw->st_mode == S_IFDIR || dirRaw->st_mode == 16877)
				{
					ft_dirAdd(&dirLst[2], ft_dirnew(dirRaw->st_mode, argv[tab[0] - 1]));
				tab[3] = 1;
				//printf("Directory test:%d, mode value:%d, dirRaw->mode:%d, operand name:%s, tab[0]:%d, i:%d, ifdir:%d\n", tab[0] - 1, dirLst[2]->mode, dirRaw->st_mode, dirLst[2]->name, tab[0], i, S_IFDIR);
				}
				else
				{
					ft_dirAdd(&dirLst[1], ft_dirnew(dirRaw->st_mode, argv[tab[0] - 1]));
				tab[2] = 1;
				//printf("second Directory test:%d, mode value:%d, operand name:%s, tab[0]:%d, i:%d, ifdir:%d\n", tab[0] - 1, dirLst[1]->mode, dirLst[1]->name, tab[0], i, S_IFDIR);
				}
				//int i = ((dirLst[1]->mode) & (1 << 14)) > 0;
			}
			tab[0]++;
				//printf("Directory test:%d, mode value:%d,  operand name:%s\n", tab[0] - 2, dirLst[1]->next->mode, dirLst[1]->next->name);
		}
	else
	{
		//ft_putendl(".");
		ft_getStat(".", &dirRaw);
		ft_dirAdd(&dirLst[2], ft_dirnew(dirRaw->st_mode, "."));
		//printf(".->mode:%d\n", dirLst[1]->mode);
		tab[3] = 1;
	}
	if (tab[1] == 1)
	{
		/*check = dirLst[0];
		while (check)
		{
			printf("check: %s\n", check->name);
			check = check->next;
		}*/
		ft_sort_dir(&dirLst[0]);
		check = dirLst[0];
		while (check)
		{
			errno = 2;
			ft_putstr("ls: ");
			perror(check->name);
			check = check->next;
		}
		free(dirLst[0]);
	}
	if (tab[2] == 1)
	{
		ft_sort_dir(&dirLst[1]);
		free(dirLst[1]);
	}
	if (tab[3] == 1)
	{
		ft_sort_dir(&dirLst[2]);
		ft_openDirecto(&dirLst[2], options, NULL);
		free(dirLst[2]);
	}
	return (0);
}
