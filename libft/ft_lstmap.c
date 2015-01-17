/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 00:48:39 by sly               #+#    #+#             */
/*   Updated: 2015/01/17 05:09:29 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*lstret;
	t_list		*lsttmp;
	t_list		*crsr;

	if (!lst || !f || !(lstret = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	lstret = f(lstret);
	crsr = lstret;
	while (lst->next)
	{
		lst = lst->next;
		if (!(lsttmp = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		crsr->next = f(lsttmp);
		crsr = crsr->next;
	}
	return (lstret);
}
