/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:37:53 by corellan          #+#    #+#             */
/*   Updated: 2023/12/22 16:04:24 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static char	*match_path(t_pipex *pipex, char **possibles)
{
	size_t	i;
	char	*path;

	i = 0;
	path = NULL;
	while (possibles[i])
	{
		path = ft_strjoin(possibles[i], pipex->cmd[0]);
		if (!path)
			return (NULL);
		if (!access(path, F_OK | X_OK))
		{
			ft_free_split(possibles);
			possibles = NULL;
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	ft_free_split(possibles);
	possibles = NULL;
	pipex->error_flag = NOTFOUND;
	return (ft_strdup(""));
}

char	*find_path(char *input, t_pipex *pipex)
{
	char	**possibles;
	size_t	size_split;
	size_t	index;

	if (ft_strlen(input) && !access(input, F_OK | X_OK))
		return (ft_strdup(input));
	size_split = ft_split_length(pipex->envp);
	index = find_in_env(pipex->envp, "PATH=");
	if (index == size_split || !pipex->envp[index][5])
	{
		pipex->error_flag = NOPATH;
		return (ft_strdup(""));
	}
	if (!ft_strlen(input))
	{
		pipex->error_flag = EMPTYCOMMAND;
		return (ft_strdup(""));
	}
	possibles = make_possibles(index, pipex);
	if (!possibles)
		return (NULL);
	return (match_path(pipex, possibles));
}
