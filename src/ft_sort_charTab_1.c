/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_charTab_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 02:03:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/22 20:16:19 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
//#include <stdio.h>

void			ft_sort_charTab(char ***argv, int argc, int start)
{
	int			i;
	int			j;
	char		*tmp;

	i = start;
	while (i < argc)
	{
		tmp = (*argv)[i];
		j = i;
		while ((j > start - 1) && (ft_strcmp((*argv)[j - 1], tmp) > 0))
		{
		//printf("start:%d, i:%d, *tmp:%s, argv[i - 1]:%s, (*argv)[i]:%s, ft_strcmp((*argv)[i - 1], tmp):%d\n", start, i, tmp, (*argv)[i - 1], (*argv)[i], ft_strcmp((*argv)[i - 1], tmp));
			(*argv)[j] = (*argv)[j - 1];
			j--;
		}
		(*argv)[j] = tmp;
		i++;
	}
}
