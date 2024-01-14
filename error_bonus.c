/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:39:11 by corellan          #+#    #+#             */
/*   Updated: 2024/01/14 12:43:06 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (error == DOTCASE)
	{
		ft_putendl_fd(".: not allowed operation for security reasons", 2);
		return ;
	}
	ft_putstr_fd("pipex: ", 2);
	if (error == PIPEERROR || error == FORKERROR || error == NOERROR || \
		error == PIDALLOC || error == PATHALLOC || error == CMDALLOC || \
		error == TMPCMDALLOC || error == LISTALLOC)
	{
		perror(str);
		return ;
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	if (error == NOPERMISION)
		ft_putendl_fd(strerror(13), 2);
	else if (error == NOFILEORDIRECTORY || error == NOPATH)
		ft_putendl_fd(strerror(2), 2);
	else if (error == NOTFOUND || error == EMPTYCOMMAND)
		ft_putendl_fd("command not found", 2);
	else if (error == DIRECTORY)
		ft_putendl_fd(strerror(21), 2);
	else if (error == HEREDOCERROR)
		ft_putendl_fd("error creating heredoc", 2);
}

int	handle_system_error(t_pipex *pipex, int error)
{
	close_fd_interface_error(pipex, error);
	if (error == HEREDOCERROR)
		print_error(HEREDOCERROR, "heredoc_creation_error");
	else if (error == PIDALLOC)
		print_error(PIDALLOC, "pid_alloc_error");
	else if (error == PATHALLOC)
		print_error(PATHALLOC, "path_alloc_error");
	else if (error == CMDALLOC)
		print_error(CMDALLOC, "cmd_alloc_error");
	else if (error == PIPEERROR)
		print_error(PIPEERROR, "pipe_creation_error");
	else if (error == FORKERROR)
		print_error(FORKERROR, "fork_error");
	else if (error == TMPCMDALLOC)
		print_error(TMPCMDALLOC, "error allocating content for list");
	else if (error == LISTALLOC)
	{
		print_error(LISTALLOC, "error allocating list node");
		free(pipex->cmd_tmp);
		pipex->cmd_tmp = NULL;
	}
	wait_interface(pipex);
	free_interface(pipex);
	return (1);
}
