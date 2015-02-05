/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 05:04:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/04 19:08:35 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_LS_H
#define FT_LS_H
#define OPTION_NB 5

typedef struct		s_dir
{
	int				mode;
	char			*name;
	struct s_dir	*next;
}					t_dir;

void				ft_run(int argc, char ** argv, int i, char *options);
void				ft_errorNonDirectoryOperand(char *s);
void				ft_sort(t_dir **dirLst);
void				ft_openDirectory(t_dir **dirLst);
#	endif
