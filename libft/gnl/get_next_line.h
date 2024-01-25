/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:00:18 by corellan          #+#    #+#             */
/*   Updated: 2024/01/25 11:26:09 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef MAX_FILES
#  define MAX_FILES 256
# endif

# include <stdlib.h>

typedef struct s_gnl
{
	int		flag;
	int		ret;
	int		alloc_flag;
	int		idx;
	size_t	n_position;
	size_t	length;
	size_t	size_alloc;
	char	*line;
	char	*buf;
	char	*temp;

}	t_gnl;

typedef struct s_colector
{
	char	*stack;
	int		fds;

}	t_colector;

int		ft_detect_index(int fd, t_colector *sample);
char	*get_next_line(int fd);

#endif
