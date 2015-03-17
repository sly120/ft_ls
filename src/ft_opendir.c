/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/03/17 22:28:43 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*static void			ft_free_t_ent(t_ent *entLst)
{
	t_ent			*csr;

	if (!entLst)
		return ;
	while (entLst)
	{
		csr = entLst;
		entLst = entLst->next;
		free(csr->name);
		free(csr);
	}
}

static void			ft_entAdd(t_ent **entLst, t_ent *newEnt)
{
	t_ent			*csr;

	if (!entLst || !newEnt)
		return ;
	if (!*entLst)
		*entLst = newEnt;
	else
	{
		csr = *entLst;
		while (csr->next)
			csr = csr->next;
		csr->next = newEnt;
	}
}
*/
/*static unsigned char	*ft_unsignedchardup(unsigned char c)
{
	unsigned char		*ret;

	if (!(ret = (unsigned char*)malloc(sizeof(unsigned char) * 1)))
		return ('\0');
	*ret = c;
	return (ret);
}
*/

/*static t_ent		*ft_entNew(char *d_name, unsigned char d_type)
{
	t_ent			*tmp;

	if (!(tmp = (t_ent*)malloc(sizeof(t_ent))))
		return (NULL);
	//printf("gogo\n");
	tmp->name = ft_strdup(d_name);
	tmp->type = d_type;
	tmp->next = NULL;
	//printf("tmp:%s, d_type:%u", tmp->name, tmp->type);
	return (tmp);
}
*/
static int			ft_split(char ***split, char *src)
{
	int				i;

	*split = ft_strsplit(src, '/');
	i = 0;
	while ((*split)[i])
	{
		//ft_putendl((*split)[i]);
		i++;
	}
	//printf("i:%d, split:%s\n", i, (*split)[i - 1]);
	return (i - 1);
}

void				ft_disp_ent(t_ent *entLst, char *options)
{
	while (entLst)
	{
		if (ft_option_check(options, 'a') || (entLst->name)[0] != '.')
			ft_putendl(entLst->name);
		entLst = entLst->next;
	}
}

void				ft_open_dir_1(t_info *info, t_ent *entlst)
{
		ft_disp_ent(entlst, info->opt);
		//printf("entLst:%s\n", entlst->name);
		if (ft_option_check(info->opt, 'R'))
			ft_recursive_ls(info, entlst);
}

void				ft_open_dir(t_info *info, t_ent *arglst, char **split)
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
	if ((dstream = opendir(arglst->name)))
	{
		while ((dirent = readdir(dstream)))
		{
			ft_putstr(dirent->d_name);
			//printf(" d_type:%u, isdir:%d\n", dirent->d_type, dirent->d_type == DT_DIR);
			//ft_entAdd(&entLst[0], ft_entNew(dirent->d_name));
			ft_get_stat(dirent->d_name, &buf);
			ft_addentlst(&entlst, dirent->d_name, buf);
			entlst->type = dirent->d_type;
			entlst->path = ft_strdup(arglst->path);
			//printf("name:%s, dir:%u, stat:%d\n", entlst->name, entlst->type == DT_DIR, S_ISDIR(entlst->stat->st_mode));
			indic[0] = 1;
		}
		ft_sort_ent(&entlst);
		ft_open_dir_1(info, entlst);
		closedir(dstream);
	}
	else
	{
		printf("hello\n");
		split = NULL;
		ft_error_prefix(arglst->name);
	}
	if (entlst)
		ft_freeentlst(entlst);
}
