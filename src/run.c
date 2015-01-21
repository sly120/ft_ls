/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sly <sly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 06:00:20 by sly               #+#    #+#             */
/*   Updated: 2015/01/21 10:27:52 by sly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

static int				ft_openTestDir(char *path, struct stat **buf)
{
	int					ret;

	*buf = (struct stat*)malloc(sizeof(struct stat));
	if ((ret = stat(path, *buf) == -1))
		return (-1);
	//printf("mode of %s:%d\n", path, (*buf)->st_mode);
	return (0);
}

/*static int			ft_openDir(char *path)
  {
  DIR				*stream;
  struct dirent	*dirent;
  int				ret;

  if (!(stream = opendir(path)))
  return (-1);
  while ((dirent = readdir(stream)))
  ft_putendl(dirent->d_name);
  if ((ret = closedir(stream)) == -1)
  return (-1);
  return (0);
  }
  */

/*static int			ft_recursiveRun(char *path)
  {
  }
  */

void				ft_dirAdd(t_dir **dirLst, t_dir *newDir)
{
	if (!dirLst || !newDir)
		return ;
	newDir->next = *dirLst;
	*dirLst = newDir;
}

t_dir				*ft_dirnew(int d_mode, char *d_name)
{
	t_dir			*tmp;
	size_t			len;

	if (!(tmp = (t_dir*)malloc(sizeof(t_dir))))
		return (NULL);
	len = ft_strlen(d_name);
	//printf("d_name:%s ", d_name);
	if (!(tmp->name = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	//printf("malloc ok ");
	ft_memcpy(tmp->name, d_name, len);
	//(tmp->name)[len] = '\0';
	//printf("name:%s\nd_mode:%d ", tmp->name, d_mode);
	tmp->mode = d_mode;
	//printf("mode:%d\n", tmp->mode);
	tmp->next = NULL;
	//printf("tmp ok\n");
	return (tmp);
}

void				ft_run(int argc, char **argv, int i, char *options)
{
	int				temp;
	/*	
	 *	dirLst[0]: list of operands which are  not a file nor a directory
	 *	dirLst[1]: list of files
	 *	dirLst[2]: list of directories
	 */	t_dir			*(dirLst)[3];
	struct stat		*dirRaw;

	temp = 0;
	while (temp < 3)
		dirLst[temp++] = NULL;
	temp = i;
	if (argc >= temp)
		while (argc >= temp)
		{
			if (ft_openTestDir(argv[temp++ - 1], &dirRaw) == -1)
			{
				ft_dirAdd(&((dirLst)[0]), ft_dirnew(-1, argv[temp - 2]));
				//dirLst[0] = ft_dirnew(-1, argv[temp - 2]);
				//printf("adresse de dirLst[0]:%p\n", dirLst[0]);
				while (dirLst[0])
				{
					//printf("coucou\n");
					ft_putstr(ft_itoa(dirLst[0]->mode));
					ft_putstr(" ");
					ft_errorNonDirectoryOperand(dirLst[0]->name);
					dirLst[0] = dirLst[0]->next;
					//free(dirLst[0]);
				}
			}
			else
			{
				dirLst[1] = ft_dirnew(dirRaw->st_mode, argv[temp - 2]);
				printf("mode:%d, operand name:%s\n", dirLst[1]->mode, dirLst[1]->name);
			}
		}
	else
	{
		ft_putendl(".");
		ft_openTestDir(".", &dirRaw);
	}
	while (*options)
		options++;
}
