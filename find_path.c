/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:37:53 by corellan          #+#    #+#             */
/*   Updated: 2024/01/17 20:17:21 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_error	check_exec_permission(char *path, int cases)
{
	int	fd;

	fd = 0;
	if (access(path, X_OK) && cases == 0)
		return (NOPERMISIONPATH);
	else if (access(path, X_OK) && cases == 1)
		return (NOPERMISION);
	else
	{
		fd = open(path, O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			return (DIRECTORY);
		}
	}
	return (NOERROR);
}

static char	**make_possibles(size_t index, t_pipex *pipex)
{
	char	**possibles;
	char	*temp;
	size_t	i;

	possibles = ft_split(pipex->envp[index] + 5, ':');
	if (!possibles)
		return (NULL);
	i = 0;
	while (possibles[i])
	{
		temp = ft_strjoin(possibles[i], "/");
		if (!temp)
		{
			ft_free_split(possibles);
			possibles = NULL;
			return (NULL);
		}
		free(possibles[i]);
		possibles[i] = NULL;
		possibles[i] = temp;
		temp = NULL;
		i++;
	}
	return (possibles);
}

static char	*match_path(t_pipex *pipex, char ***possibles)
{
	size_t	i;
	char	*path;

	i = 0;
	path = NULL;
	while ((*possibles)[i])
	{
		path = ft_strjoin((*possibles)[i], pipex->cmd[0]);
		if (!path)
			return (NULL);
		if (!access(path, F_OK) && check_exec_permission(path, 0) != DIRECTORY)
		{
			ft_free_split(*possibles);
			(*possibles) = NULL;
			pipex->error_flag = check_exec_permission(path, 0);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	ft_free_split(*possibles);
	(*possibles) = NULL;
	pipex->error_flag = NOTFOUND;
	return (ft_strdup(""));
}

static int	check_absolute(char *input, t_pipex *pipex)
{
	if (!ft_strchr(input, '/') && ft_strncmp(input, ".\0", 2) && \
		ft_strncmp(input, "..\0", 3))
		return (-1);
	if (access(input, F_OK))
		pipex->error_flag = NOFILEORDIRECTORY;
	else
	{
		pipex->error_flag = check_exec_permission(input, 1);
		if (pipex->error_flag == NOPERMISION)
			return (0);
		if (!ft_strncmp(input, ".\0", 2))
			pipex->error_flag = DOTCASE;
	}
	return (0);
}

char	*find_path(char *input, t_pipex *pipex)
{
	char	**possibles;
	size_t	size_split;
	size_t	index;

	if (input && ft_strlen(input) && !check_absolute(input, pipex))
		return (ft_strdup(input));
	size_split = ft_split_length(pipex->envp);
	index = find_in_env(pipex->envp, "PATH=");
	if (index == size_split || !pipex->envp[index][5])
	{
		pipex->error_flag = NOPATH;
		return (ft_strdup(""));
	}
	if (!input || !ft_strlen(input))
	{
		pipex->error_flag = EMPTYCOMMAND;
		return (ft_strdup(""));
	}
	possibles = make_possibles(index, pipex);
	if (!possibles)
		return (NULL);
	return (match_path(pipex, &possibles));
}
