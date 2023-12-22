/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:37:53 by corellan          #+#    #+#             */
/*   Updated: 2023/12/22 14:18:15 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*match_path(char *input, t_pipex *pipex, char **possibles)
{
	size_t	i;
	char	*path;

	i = 0;
	path = NULL;
	while (possibles[i])
	{
		path = ft_strjoin(possibles[i], input);
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

	if (!ft_strlen(input))
	{
		pipex->error_flag = EMPTYCOMMAND;
		return (ft_strdup(""));
	}
	if (!access(input, F_OK | X_OK))
		return (ft_strdup(input));
	size_split = ft_split_length(pipex->envp);
	index = find_in_env(pipex->envp, "PATH=");
	if (index == size_split || !pipex->envp[index][5])
	{
		pipex->error_flag = NOPATH;
		return (ft_strdup(""));
	}
	possibles = ft_split((pipex->envp[index]) + 5, ':');
	if (!possibles)
		return (NULL);
	return (match_path(input, pipex, possibles));
}
