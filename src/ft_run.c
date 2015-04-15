/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:26:10 by sly               #+#    #+#             */
/*   Updated: 2015/04/15 23:58:13 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void				ft_putstr_n(char *s, int n)
{
	int					i;

	i = 0;
	while (*s && i < n)
	{
		write(1, s++, 1);
		i++;
	}
}

void					ft_init_info(t_info *info, int argc, int i)
{
	info->ac = argc;
	info->pos = i;
	info->maxlink = 0;
	info->maxusername = 0;
	info->maxgroup = 0;
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
	return (lstat(path, *buf));
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

static int				ft_calc_digits(int i)
{
	int					digits;

	digits = 0;
	if (!i)
		digits++;
	while (i)
	{
		i /= 10;
		digits++;
	}
	return (digits);
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

	if ((ft_get_stat(argv, &buf) == -1))
	{
		ft_error_prefix(argv);
		return (-1);
	}
	ft_addentlst(arglst, argv, buf);
	ft_add_path(*arglst, argv);
	return (0);
}

static void				print_type(mode_t m)
{
	S_ISREG(m) ? ft_putchar('-') : 0;
	S_ISDIR(m) ? ft_putchar('d') : 0;
	S_ISBLK(m) ? ft_putchar('b') : 0;
	S_ISCHR(m) ? ft_putchar('c') : 0;
	S_ISFIFO(m) ? (S_ISSOCK(m) ? ft_putchar('s') : ft_putchar('p')) : 0;
	S_ISLNK(m) ? ft_putchar('l') : 0;
}

static void				print_permission(mode_t m)
{
	int					i;
	int					mask;

	i = -1;
	mask = 256;
	while (++i < 9)
	{
		if (i % 3 == 0)
			m & mask ? ft_putchar('r') : ft_putchar('-');
		if (i % 3 == 1)
			m & mask ? ft_putchar('w') : ft_putchar('-');
		if (i % 3 == 2)
			m & mask ? ft_putchar('x') : ft_putchar('-');
		mask = mask >> 1;
	}
}

static int				ft_maxlink(t_ent *ent)
{
	int					tmp;
	int					max;

	max = 0;
	while (ent)
	{
		tmp = (int)ent->stat->st_nlink;
		if (tmp > max)
			max = tmp;
		ent = ent->next;
	}
	//printf("max:%d\n", max);
	return (max);
}

static int				ft_maxusername(t_ent *entlst)
{
	struct passwd		*pwd;
	int					tmp;
	int					max;
	int					uid;

	max = 0;
	while (entlst)
	{
		if (!(pwd = getpwuid(entlst->stat->st_uid)))
			tmp = ft_calc_digits((int)entlst->stat->st_uid);
		else
			tmp = ft_strlen(pwd->pw_name);
		if (tmp > max)
			max = tmp;
		entlst = entlst->next;
	}
	//printf("max:%d\n", max);
	return (max);
}

static int				ft_maxgroup(t_ent *entlst)
{
	struct group		*gr;
	int					tmp;
	int					max;
	int					gid;

	max = 0;
	while (entlst)
	{
		if (!(gr = getgrgid(entlst->stat->st_gid)))
			tmp = ft_calc_digits((int)entlst->stat->st_gid);
		else
			tmp = ft_strlen(gr->gr_name);
		if (tmp > max)
			max = tmp;
		entlst = entlst->next;
	}
	return (max);
}

static int				ft_isspecial(t_ent *entlst)
{
	while (entlst)
	{
		if (S_ISCHR(entlst->stat->st_mode) || S_ISBLK(entlst->stat->st_mode))
			return (1);
		entlst = entlst->next;
	}
	return (0);
}

static void				ft_getmaxspecial(t_info *info, t_ent *entlst)
{
	t_ent				*csr;
	int					max;

	csr = entlst;
	max = 0;
	while (csr)
	{
		if (major(csr->stat->st_rdev) > max)
			max = major(csr->stat->st_rdev);
		csr = csr->next;
	}
	//printf("maxmajor:%d\n", max);
	info->maxmajor = max;
	max = 0;
	while (entlst)
	{
		if (minor(entlst->stat->st_rdev) > max)
			max = minor(entlst->stat->st_rdev);
		entlst = entlst->next;
	}
	info->maxminor = max;
}

static int				ft_maxsize(t_ent *entlst)
{
	int					max;

	max = 0;
	while (entlst)
	{
		if ((int)entlst->stat->st_size > max)
			max = (int)entlst->stat->st_size;
		entlst = entlst->next;
	}
	return (max);
}

void					getentinfo(t_info *info, t_ent *entlst)
{
	info->maxlink = ft_maxlink(entlst);
	info->maxusername = ft_maxusername(entlst);
	info->maxgroup = ft_maxgroup(entlst);
	if ((info->special = ft_isspecial(entlst)))
		ft_getmaxspecial(info, entlst);
	else
		info->maxsize = ft_maxsize(entlst);
}

static void				spaces_to_align_right(int max, int i)
{
	int					digits;
	int					maxdigits;

	maxdigits = ft_calc_digits(max);
	digits = ft_calc_digits(i);
	while (digits++ < maxdigits)
		ft_putchar(' ');
}

static void				spaces_to_align_left(int max, char *s)
{
	int					i;

	i = ft_strlen(s);
	while (i++ < max)
		ft_putchar(' ');
	ft_putchar(' ');
}

static void				spaces_to_align_left_nbr(int max, int nbr)
{
	int					digits;

	digits = ft_calc_digits(nbr);
	while (digits++ < max)
		ft_putchar(' ');
}

static char				*print_user(uid_t uid)
{
	struct passwd		*pwd;

	ft_putchar(' ');
	if (!(pwd = getpwuid(uid)))
		return (NULL);
	else
		ft_putstr(pwd->pw_name);
	return (pwd->pw_name);
}

static char				*print_group(gid_t gid)
{
	struct group		*group;

	ft_putchar(' ');
	if (!(group = getgrgid(gid)))
		return (NULL);
	else
		ft_putstr(group->gr_name);
	return (group->gr_name);
}

static void				ft_disp_size(t_info *info, t_ent *ent)
{
	ft_putchar(' ');
	spaces_to_align_right(info->maxsize, (int)ent->stat->st_size);
	ft_putnbr((int)ent->stat->st_size);
}

static int				ft_calc_total_spaces_when_device(t_info *info)
{
	int					digits;

	digits = ft_calc_digits(info->maxmajor);
	digits += ft_calc_digits(info->maxminor);
	return (digits + 2);
}

static void				ft_disp_device(t_info *info, t_ent *ent)
{
	int					spaces;

	ft_putchar(' ');
	ft_putchar(' ');
	if (S_ISCHR(ent->stat->st_mode) || S_ISBLK(ent->stat->st_mode))
	{
		//printf("%d, major:%d, minor:%d\n", ent->stat->st_rdev, major(ent->stat->st_rdev), minor(ent->stat->st_rdev));
		spaces_to_align_right(info->maxmajor, major(ent->stat->st_rdev));
		ft_putnbr(major(ent->stat->st_rdev));
		ft_putstr(", ");
		spaces_to_align_right(info->maxminor, minor(ent->stat->st_rdev));
		ft_putnbr(minor(ent->stat->st_rdev));
	}
	else
	{
		spaces = ft_calc_total_spaces_when_device(info);
		spaces -= ft_calc_digits((int)ent->stat->st_size);
		while (spaces--)
			ft_putchar(' ');
		ft_putnbr((int)ent->stat->st_size);
	}
}

static void				ft_disp_day(char *s)
{
	ft_putchar(' ');
	ft_putstr_n(s + 4, 3);
	ft_putchar(' ');
	ft_putstr_n(s + 8, 2);
	ft_putchar(' ');
	ft_putstr_n(s + 11, 5);
	ft_putchar(' ');
}

static void				ft_disp_year(char *s)
{
	ft_putchar(' ');
	ft_putstr_n(s + 4, 3);
	ft_putchar(' ');
	ft_putstr_n(s + 8, 2);
	ft_putchar(' ');
	ft_putchar(' ');
	ft_putstr_n(s + 20, 4);
	ft_putchar(' ');
}

static void				ft_disp_link(char *path)
{
	char				*buf;
	int					bufsize;
	ssize_t				ret;

	ft_putstr(" -> ");
	if ((ret = readlink(path, buf, bufsize)) == -1)
		return ;
	else
		ft_putstr_n(buf, (int)ret);
}

static void				disp_details_l_part2(t_info *info, t_ent *ent)
{
	char				*path;
	time_t				a;

	if (info->special)
		ft_disp_device(info, ent);
	else
		ft_disp_size(info, ent);
	time(&a);
	//printf("time:%s\n", ctime(&ent->stat->st_mtime));
	//printf("now:%lo, time:%lo, ", a, ent->stat->st_mtime);
	//printf("diff:%d, condition:%d \n ", (int)(a - ent->stat->st_mtime), (int)(a - ent->stat->st_mtime) >= 15724800/* || ((int)(a - ent->stat->st_mtime < -73770399)*/ ? 1 : 0);
	if (((int)(a - ent->stat->st_mtime) >= 15724800) || (int)(a - ent->stat->st_mtime) <= -15724800)
		ft_disp_year(ctime(&ent->stat->st_mtime));
	else
		ft_disp_day(ctime(&ent->stat->st_mtime));
	ft_putstr(ent->name);
	if (S_ISLNK(ent->stat->st_mode))
	{
		//ft_display_link(ent->path);
		path = ft_entpath(ent->path, ent->name);
		ft_disp_link(path);
		free(path);
	}
	ft_putchar('\n');
}

void					disp_details_l(t_info *info, t_ent *ent)
{
	char				*tmp;

	//printf("ent:%s, mode:%d\n", ent->path, ent->stat->st_mode);
	print_type(ent->stat->st_mode);
	print_permission(ent->stat->st_mode);
	if (ft_strcmp(ent->path, "/dev"))
		ft_putchar(' ');
	ft_putchar(' ');
	spaces_to_align_right(info->maxlink, ent->stat->st_nlink);
	ft_putnbr(ent->stat->st_nlink);
	if ((tmp = print_user(ent->stat->st_uid)))
		spaces_to_align_left(info->maxusername, tmp);
	else
	{
		ft_putnbr((int)ent->stat->st_uid);
		spaces_to_align_left(info->maxusername, tmp);
	}
	if ((tmp = print_group(ent->stat->st_gid)))
		spaces_to_align_left(info->maxgroup, tmp);
	else
	{
		ft_putnbr((int)ent->stat->st_uid);
		spaces_to_align_left(info->maxusername, tmp);
	}
	disp_details_l_part2(info, ent);
}

static void				ft_disp_default(t_info *info, t_ent *entlst, int (*indic)[2])
{
	int					i;
	t_ent				*csr;

	i = 0;
	csr = entlst;
	while (csr)
	{
		if (!S_ISDIR(csr->stat->st_mode))
		{ ft_putendl(csr->name), i = 1; }
		csr = csr->next;
	}
	while (entlst)
	{
		if (S_ISDIR(entlst->stat->st_mode))
		{
			//printf("entlst name:%s\n", entlst->name);
			i ? ft_putchar('\n') : 1;
			if ((*indic)[0] > 1 && (*indic)[1])
				ft_disp_path(entlst);
			ft_open_dir(info, entlst);
			i = 1;
		}
		entlst = entlst->next;
	}
}

static void				ft_disp_lformat(t_info *info, t_ent *entlst, int (*indic)[2])
{
	int					i;
	t_ent				*csr;

	i = 0;
	getentinfo(info, entlst);
	csr = entlst;
	while (csr)
	{
		if (!S_ISDIR(csr->stat->st_mode))
		{ disp_details_l(info, csr), i = 1; }
		csr = csr->next;
	}
	while (entlst)
	{
		if (S_ISDIR(entlst->stat->st_mode))
		{
			//printf("entlst name:%s\n", entlst->name);
			i ? ft_putchar('\n') : 1;
			if ((*indic)[0] > 1 && (*indic)[1])
				ft_disp_path(entlst);
			ft_open_dir(info, entlst);
			i = 1;
		}
		entlst = entlst->next;
	}
}

static void				ft_disp(t_info *info, t_ent *entlst, int (*indic)[2])
{
	ft_sort_ent(&entlst);
	if (ft_option_check(info->opt, 'l'))
		ft_disp_lformat(info, entlst, indic);
	else
		ft_disp_default(info, entlst, indic);
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
				//printf("arg name:%s\n", arglst->name);
				S_ISDIR(arglst->stat->st_mode) ? indic[1] = 1 : 1 ;
				//printf("arglst->stat:%d\n", arglst->stat->st_mode);
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
