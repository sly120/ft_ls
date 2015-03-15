/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 20:59:25 by sly               #+#    #+#             */
/*   Updated: 2015/03/15 20:57:26 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*static void			ft_free_tabchar(char **tab, int size)
{
	int				i;

	i = 0;
	if (!tab)
		return ;
	while (i < size)
		free(tab[i]);
}*/

void				ft_recursive_ls(t_info *info, t_ent *entlst)
{
	t_ent			*csr;
	int				i;

	/*csr = entLst;
	while (csr)
	{
		printf("csr:%s\n", csr->name);
		csr = csr->next;
	}*/
	csr = entlst;
	while (csr)
	{
			/*printf("csr name:%s", csr->name);
			printf(", isdir:%d", S_ISDIR(csr->stat->st_mode));
			printf(", dirtype:%u", csr->type == DT_DIR);
			printf(", strcmp .:%d", ft_strcmp(csr->name, "."));
			printf(", strcmp ..:%d\n", ft_strcmp(csr->name, ".."));*/
		if (csr->type == DT_DIR && ft_strcmp(csr->name, ".") && ft_strcmp(csr->name, ".."))
		{
			ft_add_path(csr, csr->name);
			ft_putchar('\n');
			ft_putstr(csr->path);
			ft_putendl(":");
			ft_run_ent(info, csr);
		}
		csr = csr->next;
	}
	//printf("options:%s, count:%d\n", options, count);
}
