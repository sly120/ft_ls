/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 05:04:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/06 19:25:51 by sly              ###   ########.fr       */
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

int					ft_run(int argc, char ** argv, int i, char *options);
void				ft_errorNonDirectoryOperand(char *s);
void				ft_sort(t_dir **dirLst);
void				ft_openDirectory(t_dir **dirLst);
#	endif
