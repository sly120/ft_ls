/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:26:42 by sly               #+#    #+#             */
/*   Updated: 2015/02/06 21:33:48 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <dirent.h>

#include <stdio.h>

void				ft_openDirectory(t_dir **dirLst)
{
	t_dir			*csr;
	DIR				*dstream;
	struct dirent	*dirent;

	if (!dirLst)
		return ;
	csr = *dirLst;
	while (csr)
	{
		if ((dstream = opendir(csr->name)))
		{
			while ((dirent = readdir(dstream)) != NULL)
			{
				ft_putendl(dirent->d_name);
			}
			(void)closedir(dstream);
		}
		else
		{
			printf("errno:%d\n", errno);
			perror(csr->name);
		}
		csr = csr->next;
	}
}
