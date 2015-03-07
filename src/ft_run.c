/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:26:10 by sly               #+#    #+#             */
/*   Updated: 2015/03/08 00:01:06 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>

#include <stdio.h>

void					ft_init_info(t_info *info, int argc, char **argv, int i)
{
	info->ac = argc;
	info->av = argv;
	info->pos = i;
	info->is_inrec = 0;
}

static int				ft_getStat(char *path, struct stat **buf)
{
	*buf = (struct stat*)malloc(sizeof(struct stat));
	return (stat(path, *buf));
}

void				ft_entAdd(t_ent **arglst, t_ent *new)
{
	if (!arglst || !new)
		return ;
	new->next = *arglst;
	*arglst = new;
}

void			ft_add_path(t_ent *ent, char *name)
{
	char		*s;
	int			len;

	if (!ent->path)
	{
		ent->path = ft_strdup(name);
		return ;
	}
	len = ft_strlen(ent->path) + ft_strlen(name) + 2;
	s = (char*)malloc(sizeof(char) * len);
	s = ft_strcpy(s, ent->path);
	s = ft_strcat(s, "/");
	s = ft_strcat(s, name);
	free(ent->path);
	ent->path = s;
}

t_ent			*ft_entFactory(char *name)
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
/*
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

static void				ft_init_arglst(t_ent *(*arglst)[4], int n)
{
	register int		i;

	i = 0;
	while (i < n)
		*arglst[i++] = NULL;
}
*/
static void				ft_disp_self_name(char *name)
{
	ft_putstr(name);
	ft_putendl(":");
}

static int				ft_isOperand(t_ent **arglst, char *argv)
{
	struct stat			*buf;

	/*ft_entAdd(arglst[0], ft_entFactory(argv[i - 1]));
	printf("argv:%s, %p\n", argv[i - 1], arglst[0]);
		if (ft_getStat(argv[i - 1], &((*(arglst[0]))->stat)) == -1)
		{
			ft_entAdd(arglst[1], *(arglst[0]));
			arglst[0] = NULL;
		}*/
	if ((ft_getStat(argv, &buf) == -1))
	{
		ft_error_prefix(argv);
		return (-1);
	}
	ft_entAdd(arglst, ft_entFactory(argv));
	(*arglst)->stat = buf;
	return (0);
}

static int				ft_disp(t_info *info, t_ent *arglst,char* name, int *i)
{
	if (S_ISDIR(arglst->stat->st_mode))
	{
		ft_add_path(arglst, name);
		ft_openDirecto(info, arglst, NULL);
	}
	else
		ft_putendl(name);
	*i = 1;
	return (0);
}

void					ft_run_1(t_info *info)
{
	/*
	 *	arglst[0]: list of files
	 *	arglst[1]: list of directories
	 *	inttab[0]: count
	 *	inttab[1]: isdirLst[0] indicator
	 *	inttab[2]: isdirLst[1] indicator
	 *	inttab[3]: isdirLst[2] indicator
	 */
	t_ent				*arglst;
	int					indic;
	int					i;

	//ft_init_inttab(&inttab, 4);
	//printf("inttab:%d\n", inttab[3]);
	//ft_init_arglst(&arglst, 4);
	//printf("arglst[0]:%p, arglst[1]:%p, arglst[2]:%p, arglst[0]:%p\n", &arglst[0], &arglst[1], &arglst[2], &arglst[3]);
	i = info->pos;
	indic = 0;
	arglst = NULL;
	if (i <= info->ac)
		while (i <= info->ac)
		{
			if (!(ft_isOperand(&arglst, info->av[i - 1])))
			{
				if (info->pos < info->ac)
					ft_disp_self_name(info->av[i - 1]);
				//printf("arglst->stat:%d\n", arglst->stat->st_mode);
				ft_disp(info, arglst, info->av[i - 1], &indic);
				if (i++ < info->ac)
					ft_putchar('\n');
			}
		}
	else
	{
		ft_isOperand(&arglst, ".");
		//printf(". arglst[0]->stat:%d\n", arglst->stat->st_mode);
		ft_disp(info, arglst, ".", &indic);
	}
	//!!!!!!!!free
	//printf("i:%d, argc:%d\n", i, argc);
}

int							ft_run(int argc, char **argv, int i, char *options)
{
	t_info					info;

	if (i == -1)
		return (-1);
	ft_init_info(&info, argc, argv, i);
	info.opt = options;
	//printf("info options:%s, argc:%d, argv[0]:%s, is_inrec:%d\n", info.opt, info.ac, info.av[2], info.is_inrec);
	ft_run_1(&info);
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
