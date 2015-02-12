/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 20:59:25 by sly               #+#    #+#             */
/*   Updated: 2015/02/12 20:24:08 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>

#include <stdio.h>

static char			**ft_t_entToCharTab(t_ent *entLst, int n)
{
	char			**tab;
	t_ent			*csr;
	int				i;

	if (!(tab = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	csr = entLst;
	i = 0;
	while (csr)
	{
		if (csr->type == DT_DIR)
		{
			//printf("csr before:%s\n", csr->name);
			if ((ft_strcmp(csr->name, ".")) && (ft_strcmp(csr->name, "..")))
			{
				tab[i++] = ft_strdup(csr->name);
				//printf("csr name:%s, tab i:%s\n", csr->name, tab[i - 1]);
			}
		}
		csr = csr->next;
	}
	tab[i] = NULL;
	return (tab);
}

void				ft_recursive_ls(t_ent *entLst, char *options)
{
	t_ent			*csr;
	int				count;
	char			**tab;

	count = 0;
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
			count++;
		csr = csr->next;
	}
	//printf("options:%s, count:%d\n", options, count);
	if (count > 0)
	{
		tab = ft_t_entToCharTab(entLst, count);
		if (!tab)
			return ;
		/*count = 0;
		while (tab[count])
		{
			printf("tab:%s\n", tab[count++]);//, ft_strcmp(entLst->name, "."));
		}*/
		ft_run(count, tab, 1, options);
		(void)options;
	}
}
