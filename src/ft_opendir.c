/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/03/08 00:01:05 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>

#include <stdio.h>

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

void				ft_disp_dirent(t_ent *entLst, char *options)
{
	while (entLst)
	{
		if (ft_option_check(options, 'a') || (entLst->name)[0] != '.')
			ft_putendl(entLst->name);
		entLst = entLst->next;
	}
}

void				ft_openDirecto(t_info *info, t_ent *entLst, char **split)
{
	/*
	 * indic[0]: isdirent indicator
	 * indic[1]: intermediate variable for last split element
	 */
	int				indic[2];
	DIR				*dstream;
	struct dirent	*dirent;
	t_ent			*entlst;
	t_ent			*csr;

	indic[0] = 0;
	indic[1] = 0;
	entlst = NULL;
	if ((dstream = opendir(entLst->name)))
	{
		while ((dirent = readdir(dstream)))
		{
			//ft_putstr(dirent->d_name);
			//printf(" d_type:%u, isdir:%d\n", dirent->d_type, dirent->d_type == DT_DIR);
			//ft_entAdd(&entLst[0], ft_entNew(dirent->d_name));
			ft_entAdd(&entlst, ft_entFactory(dirent->d_name));
			indic[0] = 1;
		}
		ft_sort_ent(&entlst);
		ft_disp_dirent(entlst, info->opt);
		//printf("options:%d\n", tab[1]);
		/*if (ft_option_check(options, 'R'))
			ft_recursive_ls(entLst[0], options);
		ft_free_t_ent(entLst[0]);*/
		//printf("\nok\n");
		(void)closedir(dstream);
	}
	else
	{
		printf("hello\n");
		split = NULL;
		indic[1] = ft_split(&split, entLst->name);
		ft_error_prefix(split[indic[1]]);
		free(split);
	}
}