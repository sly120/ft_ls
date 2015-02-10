/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 20:59:25 by sly               #+#    #+#             */
/*   Updated: 2015/02/10 21:46:26 by sly              ###   ########.fr       */
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

	if (!(tab = (char**)malloc(sizeof(char*) * (n - 1))))
		return (NULL);
	csr = entLst;
	i = 0;
	while (csr && i < n - 1)
	{
		if (ft_strcmp(csr->name, ".") == 0 || ft_strcmp(csr->name, "..") == 0)
			csr = csr->next;
		tab[i++] = ft_strdup(csr->name);
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
	csr = entLst;
	while (csr)
	{
		count++;
		csr = csr->next;
	}
	//printf("options:%s, count:%d\n", options, count);
	if (count > 0)
	{
		tab = ft_t_entToCharTab(entLst, count);
		if (!tab)
			return ;
		count = 0;
		while (tab[count])
		{
			printf("tab:%s\n", tab[count++]);
		}
		(void)options;
	}
}
