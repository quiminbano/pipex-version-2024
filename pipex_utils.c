/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:58:51 by corellan          #+#    #+#             */
/*   Updated: 2024/01/06 15:50:23 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_signal(char *cmd, int exit_st)
{
	if (WTERMSIG(exit_st) == SIGSEGV)
		ft_putstr_fd("pipex: segmentation fault  ", 2);
	else if (WTERMSIG(exit_st) == SIGBUS)
		ft_putstr_fd("pipex: bus error  ", 2);
	else if (WTERMSIG(exit_st) == SIGKILL)
		ft_putstr_fd("pipex: killed  ", 2);
	else if (WTERMSIG(exit_st) == SIGABRT)
		ft_putstr_fd("pipex: abort  ", 2);
	else if (WTERMSIG(exit_st) == SIGQUIT)
		ft_putstr_fd("pipex: quit  ", 2);
	else if (WTERMSIG(exit_st) == SIGPIPE)
		return (128 + WTERMSIG(exit_st));
	else
		ft_putstr_fd("pipex: unknown signal  ", 2);
	ft_putendl_fd(cmd, 2);
	return (128 + WTERMSIG(exit_st));
}

void	wait_interface(t_pipex *pipex)
{
	size_t	j;
	t_list	*iter;
	int		exit_st;

	j = 0;
	iter = pipex->lst_cmd;
	while (j < pipex->i)
	{
		waitpid(pipex->pid[j], &exit_st, 0);
		if (WIFSIGNALED(exit_st) != 0)
			pipex->exit_program = get_signal((char *)iter->content, exit_st);
		else
			pipex->exit_program = WEXITSTATUS(exit_st);
		j++;
		iter = iter->next;
	}
}

void	free_interface(t_pipex *pipex)
{
	if (pipex->lst_cmd)
	{
		ft_lstclear(&pipex->lst_cmd, &free);
		pipex->lst_cmd = NULL;
	}
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
