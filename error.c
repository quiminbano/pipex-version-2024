/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:39:11 by corellan          #+#    #+#             */
/*   Updated: 2023/12/21 17:22:58 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error, char *str)
{
	ft_putendl_fd("pipex: ", 2);
	ft_putend_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (error == OPENIN || error == OPENOUT)
		ft_putendl_fd(strerror(2), 2);
	else if (error == PIDALLOC || error == PATHALLOC || error == CMDALLOC)
		ft_putendl_fd(strerror(12), 2);
}

void	free_interface(t_pipex *pipex)
{
	if (pipex->pid)
	{
		free(pipex->pid);
		pipex->pid = NULL;
	}
	if (pipex->cmd)
	{
		ft_free_split(pipex->cmd);
		pipex->cmd = NULL;
	}
	if (pipex->path)
	{
		free(pipex->path);
		pipex->path = NULL;
	}
}

int	handle_system_error(t_pipex *pipex, int error)
{
	if (error == PIDALLOC)
		print_error(PIDALLOC, "pid_alloc_error");
	else if (error == PATHALLOC)
		print_error(PATHALLOC, "path_alloc_error");
	else if (error == CMDALLOC)
		print_error(CMDALLOC, "cmd_alloc_error");
	free_interface(pipex);
	return (1);
}
