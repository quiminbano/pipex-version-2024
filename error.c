/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:39:11 by corellan          #+#    #+#             */
/*   Updated: 2023/12/22 14:21:40 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error, char *str)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (error == OPENIN || error == OPENOUT || error == NOPATH)
		ft_putendl_fd(strerror(2), 2);
	else if (error == PIDALLOC || error == PATHALLOC || error == CMDALLOC)
		ft_putendl_fd(strerror(12), 2);
	else if (error == EMPTYCOMMAND || error == NOTFOUND)
		ft_putendl_fd("command not found", 2);
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
