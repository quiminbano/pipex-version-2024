/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:19:12 by corellan          #+#    #+#             */
/*   Updated: 2023/12/22 11:54:31 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_child_process(t_pipex *pipex)
{
	dup2(pipex->fd[OUTPUT], STDOUT_FILENO);
	close(pipex->fd[OUTPUT]);
	dup2(pipex->fd[INPUT], STDIN_FILENO);
	close(pipex->fd[INPUT]);
	if (pipex->i < (pipex->ammount_cmd - 1))
	{
		close(pipex->pipes[INPUT]);
		close(pipex->outfile);
	}
	if (pipex->error_flag != NOERROR || \
		execve(pipex->path, pipex->cmd, pipex->envp) == -1)
	{
		print_error(pipex->error_flag, pipex->cmd[0]);
		free_interface(pipex);
		exit(EXIT_FAILURE);
	}
}

static int	execute_and_close(t_pipex *pipex)
{
	if (!pipex->pid)
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

static int	process_cmd(char *input, t_pipex *pipex)
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

static int	ft_pipex(int ac, char **av, t_pipex *pipex)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		print_error(OPENIN, av[1]);
	pipex->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		print_error(OPENOUT, av[ac - 1]);
	if (pipex->infile == -1 && pipex->outfile == -1)
		return (1);
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->ammount_cmd);
	if (!pipex->pid)
		return (handle_system_error(pipex, PIDALLOC));
	while (pipex->i < pipex->ammount_cmd)
	{
		pipex->error_return = process_cmd(av[(pipex->i) + 2], pipex);
		if (pipex->error_return)
			return (handle_system_error(pipex, pipex->error_return));
		pipex->error_flag = NOERROR;
		(pipex->i)++;
	}
	pipex->i = 0;
	while (pipex->i < pipex->ammount_cmd)
		waitpid(pipex->pid[(pipex->i)++], NULL, 0);
	free_interface(pipex);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	pipex.envp = envp;
	if (ac != 5)
	{
		if (ac < 5)
			ft_putendl_fd("pipex: Not enough arguments.", 2);
		else
			ft_putendl_fd("pipex: Too many arguments.", 2);
		return (1);
	}
	pipex.ammount_cmd = (ac - 3);
	return (ft_pipex(ac, av, &pipex));
}
