/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/03/24 21:14:03 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static char			*ft_endpath(char *path)
{
	char			*s;
	int				i;

	i = ft_strlen(path);
	s = path + i;
	while (*s != '/' && i-- >= 0)
		s--;
	return (++s);
}

static char			*ft_entpath(char *argpath, char *name)
{
	char			*tmp;
	char			*dst;

	tmp = ft_strjoin(argpath, "/");
	dst = ft_strjoin(tmp, name);
	free(tmp);
	return (dst);
}

void				ft_disp_ent(t_info *info, t_ent *entlst)
{
	int				max;

	getentinfo(info, entlst);
	while (entlst)
	{
		if (ft_option_check(info->opt, 'a') || (entlst->name)[0] != '.')
		{
			if (ft_option_check(info->opt, 'l'))
			{
				disp_details_l(entlst, info->maxlink);
				ft_putchar('\n');
			}
			else
				ft_putendl(entlst->name);
		}
		entlst = entlst->next;
	}
}

void				ft_open_dir_1(t_info *info, t_ent *entlst)
{
		ft_disp_ent(info, entlst);
		//printf("entLst:%s\n", entlst->name);
		if (ft_option_check(info->opt, 'R'))
			ft_recursive_ls(info, entlst);
}

void				ft_open_dir(t_info *info, t_ent *arglst)
{
	/*
	 * indic[0]: isdirent indicator
	 * indic[1]: intermediate variable for last split element
	 */
	int				indic[2];
	DIR				*dstream;
	struct dirent	*dirent;
	t_ent			*entlst;
	struct stat		*buf;
	char			*entpath;

	indic[0] = 0;
	indic[1] = 0;
	entlst = NULL;
	dirent = (struct dirent*)malloc(sizeof(struct dirent));
	//printf("arglst path:%s\n", arglst->path);
	if ((dstream = opendir(arglst->path)))
	{
		while ((dirent = readdir(dstream)))
		{
			//ft_putstr(dirent->d_name);
			//printf(" d_type:%u, isdir:%d\n", dirent->d_type, dirent->d_type == DT_DIR);
			//ft_entAdd(&entLst[0], ft_entNew(dirent->d_name));
			//entpath = ft_entpath(arglst->path, dirent->d_name);
			ft_get_stat(dirent->d_name, &buf);
			//free(entpath);
			ft_addentlst(&entlst, dirent->d_name, buf);
			entlst->type = dirent->d_type;
			entlst->path = ft_strdup(arglst->path);
			//printf("name:%s, dir:%u, stat:%d, path:%s\n", entlst->name, entlst->type == DT_DIR, S_ISDIR(entlst->stat->st_mode), entlst->path);
			indic[0] = 1;
	printf("ent:%s, mode:%d, path:%s\n", entlst->name, entlst->stat->st_mode, entlst->path);
		}
		ft_sort_ent(&entlst);
		ft_open_dir_1(info, entlst);
		closedir(dstream);
	}
	else
		ft_error_prefix(ft_endpath(arglst->name));
	if (entlst)
		ft_freeentlst(entlst);
}
