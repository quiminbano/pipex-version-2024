/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:58:51 by corellan          #+#    #+#             */
/*   Updated: 2023/12/29 17:47:10 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_interface(t_pipex *pipex)
{
	size_t	j;

	j = 0;
	while (j < pipex->i)
	{
		waitpid(pipex->pid[j], NULL, 0);
		j++;
	}
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

size_t	find_in_env(char **envp, char *needle)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], needle, ft_strlen(needle)))
			break ;
		i++;
	}
	return (i);
}
