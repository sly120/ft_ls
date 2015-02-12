/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_ent_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/08 16:41:21 by sly               #+#    #+#             */
/*   Updated: 2015/02/12 19:01:17 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

#include <stdio.h>

t_ent			**ft_t_entToTab(t_ent **entLst, int n)
{
	t_ent				**tab;
	t_ent				*csr;
	int					i;
    
	if (!(tab = (t_ent**)malloc(sizeof(t_ent*) * n)))
		return (NULL);
	i = 0;
	csr = *entLst;
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

static void					ft_relink(t_ent ***entTab, int n, int r)
{
	int					i;

	if (!r)
	{
	i = -1;
	while (++i < n - 1)
	{
		//printf("(*entTab[i])->name:%s, (*entTab[i - 1])->name:%s, i:%d\n", (*entTab)[i]->name, (*entTab)[i + 1]->name, i);
		(*entTab)[i]->next = (*entTab)[i + 1];
	}
	(*entTab)[i]->next = NULL;
	**entTab = (*entTab)[0];
	}
	else
	{
	while (--n > 0)
	{
		/*printf("(*entTab[n])->name:%s, (*entTab[n - 1])->name:%s, n:%d\n", ((*entTab)[n])->name, ((*entTab)[n - 1])->name, n);*/
		((*entTab)[n])->next = (*entTab)[n - 1];
	}
	((*entTab)[0])->next = NULL;
	**entTab = (*entTab)[0];
	}
}

static void					ft_insertionSort_name(t_ent ***entTab, int n, int r)
{
	int					i;
	int					j;
	t_ent				*tempEnt;
    
	i = 1;
	while (i < n)
	{
        //printf("toc toc toc\n");
		tempEnt = (*entTab)[i];
		j = i;
		//printf("oyo\n");
		while ((j > 0) && (ft_strcmp(((*entTab)[j - 1])->name, tempEnt->name)) > 0)
		{
			//printf("(*entTab[j])->name:%s, (*entTab[j - 1])->name:%s, j:%d\n", ((*entTab)[j])->name, ((*entTab)[j - 1])->name, j);
			(*entTab)[j] = (*entTab)[j - 1];
			j--;
		}
		(*entTab)[j] = tempEnt;
		i++;
	}
		ft_relink(entTab, n, r);
}

void					ft_sort_ent(t_ent **entLst)
{
	t_ent				*csr;
	t_ent				**entTab;
	int					count;
	int					r;
	int					i;
    
	count = 0;
	r = 0;
	csr = *entLst;
	while (csr)
	{
		count++;
		csr = csr->next;
	}
	/*csr = *entLst;
	while (csr)
	{
		printf("name:%s\n", csr->name);
		csr = csr->next;
	}
    printf("count:%d\n", count);*/
	entTab = ft_t_entToTab(entLst, count);
	/*i = 0;
     while (i < count)
     {
     printf("name:%s, i:%d, count:%d\n", ((entTab)[i])->name, i, count);
     i++;
     }*/
	ft_insertionSort_name(&entTab, count, r);
	/*i = 0;
     while (i < count)
     {
     printf("name:%s, i:%d, count:%d\n", ((entTab)[i])->name, i, count);
     i++;
     }*/
	if (!r)
		i = 0;
	else
		i = count - 1;
	*entLst = entTab[i];
	csr = *entLst;
     while (csr)
     {
     //printf("tri:%s\n", csr->name);
     csr = csr->next;
     }
}
