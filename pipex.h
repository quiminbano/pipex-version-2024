/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:20:22 by corellan          #+#    #+#             */
/*   Updated: 2023/12/29 18:18:46 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

# define MAX_FD 2
# define INPUT 0
# define OUTPUT 1

typedef struct s_pipex
{
	char	*path;
	char	**envp;
	char	**cmd;
	int		fd[MAX_FD];
	int		pipes[MAX_FD];
	int		infile;
	int		outfile;
	int		error_return;
	int		error_flag;
	int		return_value;
	pid_t	*pid;
	size_t	ammount_cmd;
	size_t	i;
}	t_pipex;

typedef enum e_error
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
	NOTFOUND,
	DIRECTORY
}	t_error;

void	print_error(int error, char *str);
int		handle_system_error(t_pipex *pipex, int error);
void	free_interface(t_pipex *pipex);
void	wait_interface(t_pipex *pipex);
size_t	find_in_env(char **envp, char *needle);
char	*find_path(char *input, t_pipex *pipex);
int		process_cmd(char *input, t_pipex *pipex);

#endif