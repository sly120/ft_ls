/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:26:10 by sly               #+#    #+#             */
/*   Updated: 2015/03/17 20:28:09 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void					ft_init_info(t_info *info, int argc, int i)
{
	info->ac = argc;
	info->pos = i;
	info->is_inrec = 0;
}

void					ft_init_inttab(int (*inttab)[2])
{
	int					i;

	i = 0;
	while (i < 2)
		(*inttab)[i++] = 0;
	return ;
}

int					ft_get_stat(char *path, struct stat **buf)
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
	char		*tmp;
	int			len;

	if (!ent->path)
	{
		ent->path = ft_strdup(name);
		return ;
	}
	tmp = ft_strjoin(ent->path, "/");
	free(ent->path);
	ent->path = ft_strjoin(tmp, name);
	free(tmp);
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

static void				ft_disp_path(t_ent *ent)
{
	ft_putstr(ent->path);
	ft_putendl(":");
}

void					ft_addentlst(t_ent **elst, char *name, struct stat *buf)
{
	ft_entAdd(elst, ft_entFactory(name));
	//printf("arglst path:%s\n", (*arglst)->path);
	(*elst)->stat = buf;
}

static int				ft_isoperand(t_ent **arglst, char *argv)
{
	struct stat			*buf;

	/*ft_entAdd(arglst[0], ft_entFactory(argv[i - 1]));
	printf("argv:%s, %p\n", argv[i - 1], arglst[0]);
		if (ft_getStat(argv[i - 1], &((*(arglst[0]))->stat)) == -1)
		{
			ft_entAdd(arglst[1], *(arglst[0]));
			arglst[0] = NULL;
		}*/
	if ((ft_get_stat(argv, &buf) == -1))
	{
		ft_error_prefix(argv);
		return (-1);
	}
	ft_addentlst(arglst, argv, buf);
	ft_add_path(*arglst, argv);
	return (0);
}

static int				ft_disp(t_info *info, t_ent *entlst, int (*indic)[2])
{
	int					i;
	t_ent				*csr;

	i = 0;
	ft_sort_ent(&entlst);
	csr = entlst;
	while (csr)
	{
		if (!S_ISDIR(csr->stat->st_mode))
			ft_putendl(csr->name); i = 1;
		csr = csr->next;
	}
	while (entlst)
	{
		if (S_ISDIR(entlst->stat->st_mode))
		{
			i ? ft_putchar('\n') : 1;
			if ((*indic)[0] > 1 && (*indic)[1])
				ft_disp_path(entlst);
			ft_open_dir(info, entlst, NULL);
			i = 1;
		}
		entlst = entlst->next;
	}
	return (0);
}

void					ft_freeentlst(t_ent *ent)
{
	t_ent				*csr;

	while (ent)
	{
		csr = ent->next;
		//printf("free:%s\n", ent->name);
		free(ent->name);
		free(ent->stat);
		free(ent->path);
		free(ent);
		ent = csr;
	}
}

void					ft_run_1(t_info *info, char **argv)
{
	/*
	 *	inttab[0]: count of existing elements
	 *	inttab[1]: dir indicator
	 */
	t_ent				*arglst;
	int					indic[2];
	int					i;

	//ft_init_inttab(&inttab, 4);
	//printf("inttab:%d\n", inttab[3]);
	//ft_init_arglst(&arglst, 4);
	//printf("arglst[0]:%p, arglst[1]:%p, arglst[2]:%p, arglst[0]:%p\n", &arglst[0], &arglst[1], &arglst[2], &arglst[3]);
	i = info->pos;
	ft_init_inttab(&indic);
	arglst = NULL;
	if (i-- <= info->ac)
	{
		while (++i <= info->ac)
			if (!(ft_isoperand(&arglst, argv[i - 1])))
			{
				indic[0]++;
				S_ISDIR(arglst->stat->st_mode) ? indic[1] = 1 : 1 ;
				//printf("arglst->stat:%d, info inrec:%d\n", arglst->stat->st_mode, info->is_inrec);

				/*if (info->pos < info->ac)
					ft_disp_path(arglst);
				if (i < info->ac)
					ft_putchar('\n');*/
			}
		if (arglst)
			ft_disp(info, arglst, &indic);
	}
	else
	{
		ft_isoperand(&arglst, ".");
		//printf(". arglst[0]->stat:%d\n", arglst->stat->st_mode);
		ft_disp(info, arglst, &indic);
	}
	if (indic[0])
		ft_freeentlst(arglst);
	//printf("i:%d, argc:%d\n", i, argc);
}

int							ft_run(int argc, char **argv, int i, char *options)
{
	t_info					info;

	if (i == -1)
		return (-1);
	ft_init_info(&info, argc, i);
	info.opt = options;
	//printf("info options:%s, argc:%d, argv[0]:%s, is_inrec:%d\n", info.opt, info.ac, info.av[2], info.is_inrec);
	ft_run_1(&info, argv);
	//free
	return (0);
}

void						ft_run_ent(t_info *info, t_ent *entry)
{
	/*while (entry)
	{
		if (entry->type == DT_DIR)
			ft_open_dir(info, entry, NULL);
		entry = entry->next;
	}*/
	printf("ahoy\n");
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
