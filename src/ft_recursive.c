/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 20:59:25 by sly               #+#    #+#             */
/*   Updated: 2015/02/15 18:37:06 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>

#include <stdio.h>

/*static void			ft_free_tabchar(char **tab, int size)
{
	int				i;

	i = 0;
	if (!tab)
		return ;
	while (i < size)
		free(tab[i]);
}*/

static char			**ft_t_entToCharTab(t_ent *entLst)
{
	char			**tab;

	if (!(tab = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	if (entLst->type == DT_DIR)
	{
		//printf("csr before:%s\n", csr->name);
		if ((ft_strcmp(entLst->name, ".")) && (ft_strcmp(entLst->name, "..")))
		{
			tab[0] = ft_strdup(entLst->name);
			//printf("csr name:%s, tab i:%s\n", csr->name, tab[i - 1]);
		}
	}
	tab[1] = NULL;
	return (tab);
}

void				ft_recursive_ls(t_ent *entLst, char *options)
{
	t_ent			*csr;
	char			**tab;

	/*csr = entLst;
	while (csr)
	{
		printf("csr:%s, type:%u\n", csr->name, csr->type);
		csr = csr->next;
	}*/
	csr = entLst;
	while (csr)
	{
		if (csr->type == DT_DIR && ft_strcmp(csr->name, ".") && ft_strcmp(csr->name, ".."))
		{
			if (!(tab = ft_t_entToCharTab(csr)))
				return ;
			ft_putchar('\n');
			ft_putstr(tab[0]);
			ft_putendl(":");
			ft_run(1, tab, 1, options);
			//ft_free_tabchar(tab, 1);
		}
		csr = csr->next;
	}
	//printf("options:%s, count:%d\n", options, count);
}
