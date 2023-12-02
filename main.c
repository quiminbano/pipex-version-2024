/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:19:12 by corellan          #+#    #+#             */
/*   Updated: 2023/09/03 19:56:07 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_pipex(int ac, char **av)
{
	int				i;
	t_pipex			pipex;

	i = 0;
	pipex.ammount_cmd = (ac - 3);
	pipex.fd[INFILE] = open(av[1], O_RDONLY);
	if (pipex.fd[INFILE] == -1)
		print_error(OPENIN, av[1], errno);
	pipex.fd[OUTFILE] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.fd[OUTFILE] == -1)
		print_error(OPENOUT, av[ac - 1], errno);
	if (pipex.fd[INFILE] == -1 && pipex.fd[OUTFILE] == -1)
		return (1);
}

int	main(int ac, char **av)
{
	if (ac != 5)
	{
		if (ac < 5)
			ft_putendl_fd("pipex: Not enough arguments.", 2);
		else
			ft_putendl_fd("pipex: Too many arguments.", 2);
		return (1);
	}
	return (ft_pipex(ac, av));
}
