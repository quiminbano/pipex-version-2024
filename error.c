/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:39:11 by corellan          #+#    #+#             */
/*   Updated: 2023/12/26 21:34:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error, char *str)
{
	if (error == OPENIN || error == OPENOUT || error == FORKERROR || \
		error == PIPEERROR)
		perror("pipex");
	else
		ft_putstr_fd("pipex: ", 2);
	if (error == EMPTYCOMMAND || error == DIRECTORY)
		ft_putstr_fd(strerror(13), 2);
	else if (error == PIDALLOC || error == PATHALLOC || error == CMDALLOC)
		ft_putstr_fd(strerror(12), 2);
	else if (error == NOPATH || error == NOTFOUND)
		ft_putstr_fd("command not found", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
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
