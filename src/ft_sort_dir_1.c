/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 11:18:12 by sly               #+#    #+#             */
/*   Updated: 2015/02/08 16:44:12 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

#include <stdio.h>

static t_dir			**ft_t_dirToTab(t_dir **dirLst, int n)
{
	t_dir				**tab;
	t_dir				*csr;
	int					i;
    
	if (!(tab = (t_dir**)malloc(sizeof(t_dir*) * n)))
		return (NULL);
	i = 0;
	csr = *dirLst;
	//printf("coucou:%p, %s\n", csr->next, csr->name);
	while (csr)
	{
		tab[i] = csr;
        //printf("tab[i] name:%s\n", (tab[i])->name);
		csr = csr->next;
		i++;
	}
	return (tab);
}

static void					ft_relink(t_dir ***dirTab, int n, int r)
{
	int					i;

	if (!r)
	{
	i = -1;
	while (++i < n - 1)
	{
		//printf("(*dirTab[i])->name:%s, (*dirTab[i - 1])->name:%s, i:%d\n", (*dirTab)[i]->name, (*dirTab)[i + 1]->name, i);
		(*dirTab)[i]->next = (*dirTab)[i + 1];
	}
	(*dirTab)[i]->next = NULL;
	**dirTab = (*dirTab)[0];
	}
	else
	{
	while (--n > 0)
	{
		/*printf("(*dirTab[n])->name:%s, (*dirTab[n - 1])->name:%s, n:%d\n", ((*dirTab)[n])->name, ((*dirTab)[n - 1])->name, n);*/
		((*dirTab)[n])->next = (*dirTab)[n - 1];
	}
	((*dirTab)[0])->next = NULL;
	**dirTab = (*dirTab)[0];
	}
}

static void					ft_insertionSort_name(t_dir ***dirTab, int n, int r)
{
	int					i;
	int					j;
	t_dir				*tempDir;
    
	i = 1;
	while (i < n)
	{
        //printf("toc toc toc\n");
		tempDir = (*dirTab)[i];
		j = i;
		//printf("oyo\n");
		while ((j > 0) && (ft_strcmp(((*dirTab)[j - 1])->name, tempDir->name)) > 0)
		{
			//printf("(*dirTab[j])->name:%s, (*dirTab[j - 1])->name:%s, j:%d\n", ((*dirTab)[j])->name, ((*dirTab)[j - 1])->name, j);
			(*dirTab)[j] = (*dirTab)[j - 1];
			j--;
		}
		(*dirTab)[j] = tempDir;
		i++;
	}
		ft_relink(dirTab, n, r);
}

void					ft_sort_dir(t_dir **dirLst)
{
	t_dir				*csr;
	t_dir				**dirTab;
	int					count;
	int					r;
	int					i;
    
	count = 0;
	r = 0;
	csr = *dirLst;
	while (csr)
	{
		count++;
		csr = csr->next;
	}
	/*csr = *dirLst;
	while (csr)
	{
		printf("name:%s\n", csr->name);
		csr = csr->next;
	}
    printf("count:%d\n", count);*/
	dirTab = ft_t_dirToTab(dirLst, count);
	/*i = 0;
     while (i < count)
     {
     printf("name:%s, i:%d, count:%d\n", ((dirTab)[i])->name, i, count);
     i++;
     }*/
	ft_insertionSort_name(&dirTab, count, r);
	/*i = 0;
     while (i < count)
     {
     printf("name:%s, i:%d, count:%d\n", ((dirTab)[i])->name, i, count);
     i++;
     }*/
	if (!r)
		i = 0;
	else
		i = count - 1;
	*dirLst = dirTab[i];
	csr = *dirLst;
     while (csr)
     {
     //printf("tri:%s\n", csr->name);
     csr = csr->next;
     }
}
