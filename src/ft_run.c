/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:26:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/19 22:56:54 by sly              ###   ########.fr       */
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
	return ((ret = stat(path, *buf)));
}

static void				ft_entAdd(t_ent **entLst, t_ent *new)
{
	t_ent				*csr;

	if (!entLst || !new)
		return ;
	if (!*entLst)
		*entLst = new;
	else
	{
		csr = *entLst;
		while (csr->next)
			csr = csr->next;
		csr->next = new;
	}
}

static t_ent			*ft_entFactory(char *name)
{
	t_ent				*tmp;

	if (!(tmp = (t_ent*)malloc(sizeof(t_ent))))
		return (NULL);
	tmp->name = ft_strdup(name);
	tmp->stat = NULL;
	tmp->path = NULL;
	tmp->next = NULL;
	return (tmp);
}

static void				ft_init_inttab(int **inttab, int n)
{
	register int		i;

	i = 0;
	while (i < n)
	{
		*inttab = (int*)malloc(sizeof(int) * n);
		inttab[i++] = 0;
	}
}

static void				ft_init_entLst(t_ent ***entLst, int n)
{
	register int		i;

	i = 0;
	while (i < n)
		entLst[i++] = NULL;
}

static int				ft_subrun(t_ent ***entLst, char **argv, int i)
{
	ft_entAdd((entLst)[0], ft_entFactory(argv[i - 1]));
	printf("hello inttab\n");
		if (ft_getStat(argv[i - 1], &((*(entLst[0]))->stat)) == -1)
		{
			ft_entAdd(entLst[1], *(entLst[0]));
			entLst[0] = NULL;
		}
		return (0);
}

int						ft_run(int argc, char **argv, int i, char *options)
{
	/*
	 *	entLst[0]: entry to test
	 *	entLst[1]: list of operands which are not a file nor a directory
	 *	entLst[2]: list of files
	 *	entLst[3]: list of directories
	 *	inttab[0]: count
	 *	inttab[1]: isdirLst[0] indicator
	 *	inttab[2]: isdirLst[1] indicator
	 *	inttab[3]: isdirLst[2] indicator
	 */
	t_ent				**entLst;
	int					*inttab;

	if (i == -1)
		return (-1);
	ft_init_inttab(&inttab, 4);
	ft_init_entLst(&entLst, 4);
	if (i <= argc)
	{
		while (i <= argc)
		{
			/*if (i > argc)
			{
				//afficher les noms des dossiers a rechercher
			}*/
		ft_subrun(&entLst, argv, i);
		}
	}
	/*else
	{
	}*/
	(void)options;
	return (0);
}

/*int						ft_run(int argc, char **argv, int i, char *options)
{
	
	 *	dirLst[0]: list of operands which are not a file nor a directory
	 *	dirLst[1]: list of files
	 *	dirLst[2]: list of directories
	 *	tab[0]: count
	 *	tab[1]: isdirLst[0] indicator
	 *	tab[2]: isdirLst[1] indicator
	 *	tab[3]: isdirLst[2] indicator
	 */
	/*t_dir				*dirLst[3];
	int					tab[4];
	struct stat			*dirRaw;
	t_dir				*check;

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
				if (S_ISDIR(dirRaw->st_mode))
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
		check = dirLst[0];
		while (check)
		{
			printf("check: %s\n", check->name);
			check = check->next;
		}*/
		/*ft_sort_dir(&dirLst[0]);
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
}*/
