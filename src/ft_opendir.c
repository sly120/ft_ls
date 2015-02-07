/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/02/07 21:19:01 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>

#include <stdio.h>

static void			ft_entAdd(t_ent **entries, t_ent *newEnt)
{
	t_ent			*csr;

	if (!entries || !newEnt)
		return ;
	if (!*entries)
		*entries = newEnt;
	else
	{
		csr = *entries;
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

void				ft_openDirectory(t_dir **dirLst, char **split)
{
	t_dir			*csr;
	DIR				*dstream;
	struct dirent	*dirent;
	t_ent			*entries;
	int				tab[2];
	//t_ent			*ent;

	csr = *dirLst;
	tab[0] = 0;
	entries = NULL;
	while (csr)
	{
		if ((dstream = opendir(csr->name)))
		{
			while ((dirent = readdir(dstream)) != NULL)
			{
				//ft_putendl(dirent->d_name);
				ft_entAdd(&entries, ft_entNew(dirent->d_name));
				tab[0] = 1;
			}
			/*ent = entries;
			while (ent)
			{
				printf("entries:%s\n", ent->name);
				ent = ent->next;
			}*/
			(void)closedir(dstream);
		}
		else
		{
			split = NULL;
			tab[1] = ft_split(&split, csr->name);
			ft_error_prefix(split[tab[1]]);
			free(split);
		}
		csr = csr->next;
	}
}
