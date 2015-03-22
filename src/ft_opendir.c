/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/03/22 23:53:47 by sly              ###   ########.fr       */
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

void				ft_disp_ent(t_ent *entlst, char *options)
{
	int				max;

	max = ft_maxlink(entlst);
	while (entlst)
	{
		if (ft_option_check(options, 'a') || (entlst->name)[0] != '.')
		{
			if (ft_option_check(options, 'l'))
			{
				disp_details_l(entlst, max);
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
		ft_disp_ent(entlst, info->opt);
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
			ft_get_stat(dirent->d_name, &buf);
			ft_addentlst(&entlst, dirent->d_name, buf);
			entlst->type = dirent->d_type;
			entlst->path = ft_strdup(arglst->path);
			//printf("name:%s, dir:%u, stat:%d, path:%s\n", entlst->name, entlst->type == DT_DIR, S_ISDIR(entlst->stat->st_mode), entlst->path);
			indic[0] = 1;
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
