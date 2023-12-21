/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:20:22 by corellan          #+#    #+#             */
/*   Updated: 2023/12/21 17:39:40 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>

# define MAX_FD 2
# define INPUT 0
# define OUTPUT 1

typedef struct s_pipex
{
	int		fd[MAX_FD];
	int		pipes[MAX_FD];
	int		infile;
	int		outfile;
	int		ammount_cmd;
	int		i;
	int		error_return;
	int		error_flag;
	pid_t	*pid;
	char	*path;
	char	**envp;
	char	**cmd;
}	t_pipex;

enum e_error
{
	NOERROR,
	OPENIN,
	OPENOUT,
	PIDALLOC,
	PATHALLOC,
	CMDALLOC,
	PIPEERROR,
	FORKERROR,
	EMPTYCOMMAND,
	NOPATH,
	NOTFOUND
}	t_error;

void	print_error(int error, char *str);
int		handle_system_error(t_pipex *pipex, int error);
void	free_interface(t_pipex *pipex);
size_t	find_in_env(char **envp, char *needle);
char	*find_path(char *input, t_pipex *pipex);

#endif