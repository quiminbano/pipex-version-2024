/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:40:20 by corellan          #+#    #+#             */
/*   Updated: 2024/01/06 11:28:21 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	append_heredoc(char **line, char **heredoc, char **temp)
{
	(*temp) = ft_strjoin((*heredoc), (*line));
	if (!(*temp))
	{
		free(*heredoc);
		free(*line);
		return (1);
	}
	free(*heredoc);
	(*heredoc) = NULL;
	(*heredoc) = (*temp);
	(*temp) = NULL;
	free(*line);
	(*line) = NULL;
	ft_putstr_fd("pipex_heredoc> ", 1);
	(*line) = get_next_line(0);
	return (0);
}

static char	*get_string(char *delimiter, t_pipex *pipex)
{
	char	*heredoc;
	char	*temp;
	char	*line;

	heredoc = NULL;
	line = NULL;
	heredoc = ft_strdup("");
	if (!heredoc)
		return (NULL);
	ft_putstr_fd("pipex_heredoc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if (!ft_strncmp(delimiter, line, SIZE_MAX))
		{
			free(line);
			break ;
		}
		pipex->error_flag = append_heredoc(&line, &heredoc, &temp);
		if (pipex->error_flag)
			return (NULL);
	}
	return (heredoc);
}

static int	heredoc_fd(char *delimiter, t_pipex *pipex)
{
	char	*heredoc;
	int		ret;
	int		fd[MAX_FD];

	heredoc = NULL;
	heredoc = get_string(delimiter, pipex);
	if (!heredoc)
		return (-1);
	if (pipe(fd) == -1)
	{
		free(heredoc);
		return (-1);
	}
	ret = write(fd[1], heredoc, ft_strlen(heredoc));
	if (ret == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free(heredoc);
		return (-1);
	}
	close(fd[1]);
	free(heredoc);
	return (fd[0]);
}

static char	*prepare_delimiter(char *delimiter)
{
	char	*new_delimiter;

	new_delimiter = NULL;
	new_delimiter = ft_strjoin(delimiter, "\n");
	if (!new_delimiter)
		return (NULL);
	return (new_delimiter);
}

int	handle_heredoc(char *delimiter, char *outfile, t_pipex *pipex)
{
	char	*new_delimiter;

	new_delimiter = NULL;
	new_delimiter = prepare_delimiter(delimiter);
	pipex->heredoc_flag = 1;
	pipex->ammount_cmd -= 1;
	if (!new_delimiter)
	{
		print_error(HEREDOCERROR, "heredoc");
		return (1);
	}
	pipex->infile = heredoc_fd(new_delimiter, pipex);
	if (pipex->infile == -1)
		print_error(HEREDOCERROR, "heredoc");
	pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (pipex->outfile == -1 && access(outfile, F_OK))
		print_error(NOFILEORDIRECTORY, outfile);
	else if (pipex->outfile == -1 && !access(outfile, F_OK))
		print_error(NOPERMISION, outfile);
	free(new_delimiter);
	return (0);
}
