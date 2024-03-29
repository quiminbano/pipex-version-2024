/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:19:12 by corellan          #+#    #+#             */
/*   Updated: 2024/01/12 12:12:15 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	files_interface(int ac, char **av, t_pipex *pipex)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1 && access(av[1], F_OK))
		print_error(NOFILEORDIRECTORY, av[1]);
	else if (pipex->infile == -1 && !access(av[1], F_OK))
		print_error(NOPERMISION, av[1]);
	pipex->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile == -1 && access(av[ac - 1], F_OK))
		print_error(NOFILEORDIRECTORY, av[ac - 1]);
	else if (pipex->outfile == -1 && !access(av[ac - 1], F_OK))
		print_error(NOPERMISION, av[ac - 1]);
	if (pipex->infile == -1 && pipex->outfile == -1)
		return (1);
	return (0);
}

static int	ft_pipex(int ac, char **av, t_pipex *pipex)
{
	if (files_interface(ac, av, pipex))
		return (1);
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->ammount_cmd);
	if (!pipex->pid)
		return (handle_system_error(pipex, PIDALLOC));
	while (pipex->i < pipex->ammount_cmd)
	{
		pipex->cmd_tmp = NULL;
		pipex->lst_tmp = NULL;
		pipex->error_return = process_cmd(av[(pipex->i) + 2], pipex);
		if (pipex->error_return)
			return (handle_system_error(pipex, pipex->error_return));
		(pipex->i)++;
	}
	wait_interface(pipex);
	free_interface(pipex);
	return (pipex->exit_program);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	pipex.envp = envp;
	if (ac != 5)
	{
		if (ac < 5)
			ft_putendl_fd("pipex: not enough arguments.", 2);
		else
			ft_putendl_fd("pipex: too many arguments.", 2);
		return (1);
	}
	pipex.ammount_cmd = (ac - 3);
	return (ft_pipex(ac, av, &pipex));
}
