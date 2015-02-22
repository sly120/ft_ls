/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 05:04:10 by sly               #+#    #+#             */
/*   Updated: 2015/02/22 02:23:00 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_LS_H
#define FT_LS_H
#define OPTION_NB 5

typedef struct		s_ent
{
	char			*name;
	struct stat		*stat;
	char			*path;
	struct s_ent	*next;
}					t_ent;

void				ft_sort_charTab(char ***argv, int argc, int start);
int					ft_readArg(int argc, char **argv, char **options);
int					ft_run(int argc, char ** argv, int i, char *options);
//void				ft_sort_dir(t_dir **dirLst);
void				ft_sort_ent(t_ent **entLst);
//void				ft_openDirecto(t_dir **dirLst, char* options, char **split);
//void				ft_free_t_ent(t_ent *entLst);
int					ft_option_check(char *options, char c);
void				ft_recursive_ls(t_ent *entLst, char *options);
void				ft_error_prefix(char *s);
#	endif
