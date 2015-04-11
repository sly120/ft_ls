/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 05:04:10 by sly               #+#    #+#             */
/*   Updated: 2015/04/11 16:46:24 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_LS_H
#define FT_LS_H
#define OPTION_NB 5
#define OPTION_POSSIBILITIES "Ralrt"

#include <libft.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

typedef struct		s_ent
{
	char			*name;
	struct stat		*stat;
	char			*path;
	unsigned char	type;
	struct s_ent	*next;
}					t_ent;

typedef struct		s_info
{
	char			*opt;
	int				ac;
	int				pos;
	int				maxlink;
	int				maxusername;
	int				maxgroup;
	int				special;
	int				maxminor;
	int				maxmajor;
}					t_info;

void				ft_sort_charTab(char ***argv, int argc, int start);
int					ft_readArg(int argc, char **argv, char **options);
int					ft_get_stat(char *path, struct stat **buf);
int					ft_run(int argc, char ** argv, int i, char *options);
t_ent				*ft_entFactory(char *name);
void				ft_entAdd(t_ent **entlst, t_ent *new);
void				ft_addentlst(t_ent **entlst, char *name, struct stat *buf);
void				ft_add_path(t_ent *ent, char *name);
void				ft_sort_ent(t_ent **entlst);
void				ft_open_dir(t_info *info, t_ent *entlst);
int					ft_option_check(char *options, char c);
void				ft_recursive_ls(t_info *info, t_ent *entlst);
void				ft_run_ent(t_info *info, t_ent *entlst);
void				getentinfo(t_info *info, t_ent *entlst);
void				disp_details_l(t_info *info, t_ent *ent);
void				ft_error_prefix(char *s);
void				ft_freeentlst(t_ent *ent);
#	endif
