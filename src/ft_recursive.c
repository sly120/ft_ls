/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 20:59:25 by sly               #+#    #+#             */
/*   Updated: 2015/03/08 22:57:46 by sly              ###   ########.fr       */
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

void				ft_recursive_ls(t_info *info, t_ent *entLst)
{
	t_ent			*csr;

	/*csr = entLst;
	while (csr)
	{
		printf("csr:%s\n", csr->name);
		csr = csr->next;
	}*/
	csr = entLst;
	while (csr)
	{
			/*printf("csr name:%s", csr->name);
			printf(", isdir:%d", S_ISDIR(csr->stat->st_mode));
			printf(", strcmp .:%d", ft_strcmp(csr->name, "."));
			printf(", strcmp ..:%d\n", ft_strcmp(csr->name, ".."));*/
		if (entLst->type == DT_DIR && ft_strcmp(csr->name, ".") && ft_strcmp(csr->name, ".."))
		{
			ft_add_path(csr, csr->name);
			ft_putchar('\n');
			ft_putstr(csr->path);
			ft_putendl(":");
			//ft_run(1, tab, 1, options);
			//ft_free_tabchar(tab, 1);
		}
		csr = csr->next;
	}
	//printf("options:%s, count:%d\n", options, count);
}
