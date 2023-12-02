/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:20:22 by corellan          #+#    #+#             */
/*   Updated: 2023/09/03 20:24:22 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define MAX_FD 2
# define INFILE 0
# define OUTFILE 1

typedef struct s_pipex
{
	int		fd[MAX_FD];
	int		*pipes[MAX_FD];
	int		ammount_cmd;
	pid_t	*pid;
}	t_pipex;

enum e_error
{
	OPENIN,
	OPENOUT
};

void	print_error(int error, char *str, int err);
char	**ft_parse_input(char *str);

#endif