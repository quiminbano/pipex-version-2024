/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:49:28 by corellan          #+#    #+#             */
/*   Updated: 2023/12/22 19:03:27 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_dup_and_close(t_pipex *pipex)
{
	if (pipex->fd[INPUT] != -1)
	{
		dup2(pipex->fd[OUTPUT], STDOUT_FILENO);
		close(pipex->fd[OUTPUT]);
	}
	if (pipex->fd[OUTPUT] != -1)
	{
		dup2(pipex->fd[INPUT], STDIN_FILENO);
		close(pipex->fd[INPUT]);
	}
	if (pipex->i < (pipex->ammount_cmd - 1))
	{
		close(pipex->pipes[INPUT]);
		if (pipex->outfile != -1)
			close(pipex->outfile);
	}
	if ((pipex->i == 0 && pipex->infile == -1) || \
		((pipex->i == (pipex->ammount_cmd - 1)) && pipex->outfile == -1))
	{
		free_interface(pipex);
		exit(EXIT_FAILURE);
	}
}

static void	run_child_process(t_pipex *pipex)
{
	handle_dup_and_close(pipex);
	if (pipex->error_flag != NOERROR || \
		execve(pipex->path, pipex->cmd, pipex->envp) == -1)
	{
		if (!pipex->cmd[0])
			print_error(pipex->error_flag, "");
		else
			print_error(pipex->error_flag, pipex->cmd[0]);
		free_interface(pipex);
		exit(EXIT_FAILURE);
	}
}

static int	execute_and_close(t_pipex *pipex)
{
	if (!pipex->pid[pipex->i])
		run_child_process(pipex);
	close(pipex->fd[OUTPUT]);
	close(pipex->fd[INPUT]);
	if (pipex->i < (pipex->ammount_cmd - 1))
	{
		pipex->fd[INPUT] = dup(pipex->pipes[INPUT]);
		close(pipex->pipes[INPUT]);
	}
	free(pipex->path);
	pipex->path = NULL;
	ft_free_split(pipex->cmd);
	pipex->cmd = NULL;
	return (NOERROR);
}

int	process_cmd(char *input, t_pipex *pipex)
{
	pipex->cmd = ft_split(input, ' ');
	if (!(pipex->cmd))
		return (CMDALLOC);
	pipex->path = find_path(input, pipex);
	if (!(pipex->path))
		return (PATHALLOC);
	if (pipex->i < (pipex->ammount_cmd - 1) && pipe(pipex->pipes) == -1)
		return (PIPEERROR);
	if (pipex->i == 0)
		pipex->fd[INPUT] = pipex->infile;
	if (pipex->i == (pipex->ammount_cmd - 1))
		pipex->fd[OUTPUT] = pipex->outfile;
	else
		pipex->fd[OUTPUT] = pipex->pipes[OUTPUT];
	pipex->pid[pipex->i] = fork();
	if (pipex->pid[pipex->i] == -1)
		return (FORKERROR);
	return (execute_and_close(pipex));
}
