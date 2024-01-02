/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:39:11 by corellan          #+#    #+#             */
/*   Updated: 2024/01/02 15:18:23 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_fd_interface_error(t_pipex *pipex, int error)
{
	if (pipex->i == 0 && pipex->infile != -1)
		close(pipex->infile);
	else if (pipex->i > 0 && pipex->fd[INPUT] != -1)
		close(pipex->fd[INPUT]);
	if (error == FORKERROR && pipex->i < (pipex->ammount_cmd - 1))
	{
		close(pipex->pipes[INPUT]);
		close(pipex->pipes[OUTPUT]);
	}
	if (pipex->outfile != -1)
		close(pipex->outfile);
}

void	print_error(int error, char *str)
{
	ft_putstr_fd("pipex: ", 2);
	if (error == EMPTYCOMMAND || error == DIRECTORY || error == NOPERMISION)
		ft_putstr_fd(strerror(13), 2);
	else if (error == PIDALLOC || error == PATHALLOC || error == CMDALLOC)
		ft_putstr_fd(strerror(12), 2);
	else if (error == NOFILEORDIRECTORY)
		ft_putstr_fd(strerror(2), 2);
	else if (error == NOPATH || error == NOTFOUND)
		ft_putstr_fd("command not found", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
}

int	handle_system_error(t_pipex *pipex, int error)
{
	close_fd_interface_error(pipex, error);
	if (error == PIDALLOC)
		print_error(PIDALLOC, "pid_alloc_error");
	else if (error == PATHALLOC)
		print_error(PATHALLOC, "path_alloc_error");
	else if (error == CMDALLOC)
		print_error(CMDALLOC, "cmd_alloc_error");
	else if (error == PIPEERROR)
		print_error(PIPEERROR, "pipe_creation_error");
	else if (error == FORKERROR)
		print_error(FORKERROR, "fork_error");
	wait_interface(pipex);
	free_interface(pipex);
	return (1);
}
