/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/02/09 21:23:46 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>

#include <stdio.h>

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

static t_ent		*ft_entNew(char *d_name)
{
	t_ent			*tmp;

	if (!(tmp = (t_ent*)malloc(sizeof(t_ent))))
		return (NULL);
	tmp->name = ft_strdup(d_name);
	tmp->next = NULL;
	return (tmp);
}

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

void				ft_openDirecto(t_dir **dirLst, char* options, char **split)
{
	/*
	 * tab[0]: is entLst indicator
	 * tab[1]: is option a indicator
	 * tab[2]: intermediate variable for last split element
	 */
	int				tab[3];
	t_dir			*csr;
	DIR				*dstream;
	struct dirent	*dirent;
	t_ent			*entLst[2];

	csr = *dirLst;
	tab[0] = 0;
	tab[1] = 0;
	entLst[0] = NULL;
	entLst[1] = NULL;
	while (csr)
	{
		if ((dstream = opendir(csr->name)))
		{
			while ((dirent = readdir(dstream)) != NULL)
			{
				//ft_putendl(dirent->d_name);
				ft_entAdd(&entLst[0], ft_entNew(dirent->d_name));
				tab[0] = 1;
			}
			ft_sort_ent(&entLst[0]);
			entLst[1] = entLst[0];
			tab[1] = ft_option_check(options, 'a');
			//printf("options:%d\n", tab[1]);
			while (entLst[1])
			{
				if (tab[1] || (entLst[1]->name)[0] != '.')
					ft_putendl(entLst[1]->name);
				entLst[1] = entLst[1]->next;
			}
			(void)closedir(dstream);
		}
		else
		{
			split = NULL;
			tab[2] = ft_split(&split, csr->name);
			ft_error_prefix(split[tab[2]]);
			free(split);
		}
		csr = csr->next;
	}
	/*if (ft_option_check(options, 'R'))
		ft_recursive_ls();*/
}
