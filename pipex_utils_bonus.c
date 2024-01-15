/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:58:51 by corellan          #+#    #+#             */
/*   Updated: 2024/01/15 23:43:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	get_signal(void *cmd, int exit_st, t_pipex *pipex, size_t j)
{
	if (j < (pipex->ammount_cmd - 1))
		return (128 + WTERMSIG(exit_st));
	ft_putstr_fd("pipex: ", 2);
	if (cmd)
		ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": ", 2);
	if (WTERMSIG(exit_st) == SIGSEGV)
		ft_putstr_fd("Segmentation fault: ", 2);
	else if (WTERMSIG(exit_st) == SIGBUS)
		ft_putstr_fd("Bus error: ", 2);
	else if (WTERMSIG(exit_st) == SIGKILL)
		ft_putstr_fd("Killed: ", 2);
	else if (WTERMSIG(exit_st) == SIGABRT)
		ft_putstr_fd("Abort: ", 2);
	else if (WTERMSIG(exit_st) == SIGQUIT)
		ft_putstr_fd("Quit: ", 2);
	else if (WTERMSIG(exit_st) == SIGPIPE)
		ft_putstr_fd("Broken pipe: ", 2);
	else
		ft_putstr_fd("Unknown signal: ", 2);
	ft_putnbr_fd(WTERMSIG(exit_st), 2);
	ft_putendl_fd("", 2);
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
			pipex->exit_program = get_signal(iter->content, exit_st, pipex, j);
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
