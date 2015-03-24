/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_ent_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/08 16:41:21 by sly               #+#    #+#             */
/*   Updated: 2015/03/16 00:22:07 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_ent			**ft_t_enttotab(t_ent **entlst, int n)
{
	t_ent				**tab;
	t_ent				*csr;
	int					i;
    
	if (!(tab = (t_ent**)malloc(sizeof(t_ent*) * n)))
		return (NULL);
	i = 0;
	csr = *entlst;
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

static void					ft_relink(t_ent ***enttab, int n, int r)
{
	int					i;

	if (!r)
	{
	i = -1;
	while (++i < n - 1)
	{
		//printf("(*entTab[i])->name:%s, (*entTab[i - 1])->name:%s, i:%d\n", (*entTab)[i]->name, (*entTab)[i + 1]->name, i);
		(*enttab)[i]->next = (*enttab)[i + 1];
	}
	(*enttab)[i]->next = NULL;
	**enttab = (*enttab)[0];
	}
	else
	{
	while (--n > 0)
	{
		/*printf("(*entTab[n])->name:%s, (*entTab[n - 1])->name:%s, n:%d\n", ((*entTab)[n])->name, ((*entTab)[n - 1])->name, n);*/
		((*enttab)[n])->next = (*enttab)[n - 1];
	}
	((*enttab)[0])->next = NULL;
	**enttab = (*enttab)[0];
	}
}

static void					ft_insertionsortbyname(t_ent ***enttab, int n, int r)
{
	int					i;
	int					j;
	t_ent				*tmp;
    
	i = 1;
	while (i < n)
	{
        //printf("toc toc toc\n");
		tmp = (*enttab)[i];
		j = i;
		//printf("oyo\n");
		while ((j > 0) && (ft_strcmp(((*enttab)[j - 1])->name, tmp->name)) > 0)
		{
			//printf("(*entTab[j])->name:%s, (*entTab[j - 1])->name:%s, j:%d\n", ((*entTab)[j])->name, ((*entTab)[j - 1])->name, j);
			(*enttab)[j] = (*enttab)[j - 1];
			j--;
		}
		(*enttab)[j] = tmp;
		i++;
	}
		ft_relink(enttab, n, r);
}

void					ft_sort_ent(t_ent **entlst)
{
	t_ent				*csr;
	t_ent				**enttab;
	int					count;
	int					r;
	int					i;
    
	count = 0;
	r = 0;
	csr = *entlst;
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
	enttab = ft_t_enttotab(entlst, count);
	/*i = 0;
     while (i < count)
     {
     printf("name:%s, i:%d, count:%d\n", ((entTab)[i])->name, i, count);
     i++;
     }*/
	ft_insertionsortbyname(&enttab, count, r);
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
	*entlst = enttab[i];
	/*csr = *entLst;
     while (csr)
     {
     //printf("tri:%s\n", csr->name);
     csr = csr->next;
     }*/
	free(enttab);
}
