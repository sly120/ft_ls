/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_charTab_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 02:03:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/22 02:41:56 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

void			ft_sort_charTab(char ***argv, int argc, int start)
{
	int			i;
	char		*tmp;

	while (start < argc)
	{
		tmp = (*argv)[i];
		i = start;
		while ((i > 0) && (ft_strcmp((*argv)[i - 1], tmp) > 0))
		{
		printf("start:%d, i:%d, *tmp:%s\n", start, i, tmp);
			(*argv)[i] = (*argv)[i - 1];
			i--;
		}
		(*argv)[i] = tmp;
		start++;
	}
}
