/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:19:12 by corellan          #+#    #+#             */
/*   Updated: 2023/12/21 18:19:35 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(t_pipex *pipex)
{
	
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
	if (!pipex->pid)
		execute_command(pipex);
	close(pipex->fd[OUTPUT]);
	close(pipex->fd[INPUT]);
	if (pipex->i < (pipex->ammount_cmd - 1))
	{
		pipex->fd[INPUT] = dup(pipex->pipes[INPUT]);
		close(pipex->pipes[INPUT]);
	}
	return (NOERROR);
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
