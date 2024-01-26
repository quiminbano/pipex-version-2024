/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:01:33 by corellan          #+#    #+#             */
/*   Updated: 2024/01/26 12:07:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

static void	ft_line_check(char **stack, t_gnl *col)
{
	size_t	i;

	i = 0;
	free(*stack);
	(*stack) = col->temp;
	while ((*stack)[col->length] != '\0')
		(col->length)++;
	while ((*stack)[i] != '\0' && (*stack)[i] != '\n')
		i++;
	if (i < col->length)
	{
		col->flag = 0;
		col->n_position = i;
		col->size_alloc = i + 1;
	}
	else
	{
		col->flag = 1;
		col->n_position = 0;
		col->size_alloc = col->length;
	}
}

static char	*ft_write_line(char **stack, t_gnl *col)
{
	col->line = (char *)malloc(sizeof(char) * (col->size_alloc + 1));
	if (!col->line)
	{
		free (*stack);
		*stack = NULL;
		return (NULL);
	}
	ft_strlcpy(col->line, *stack, (col->size_alloc + 1));
	col->temp = ft_strjoin((*stack) + (col->size_alloc), "");
	if (!col->temp)
	{
		free(col->line);
		free(*stack);
		*stack = NULL;
		return (NULL);
	}
	free(*stack);
	if (col->temp[0] == '\0')
	{
		free(col->temp);
		col->temp = NULL;
	}
	(*stack) = col->temp;
	col->temp = NULL;
	return (col->line);
}

void	ft_alloc_buf_stack(char **stack, t_gnl *col)
{
	col->buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!col->buf)
	{
		if (*stack)
		{
			free(*stack);
			*stack = NULL;
		}
		col->alloc_flag = 1;
	}
	if (!col->alloc_flag && !(*stack))
	{
		(*stack) = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*stack))
		{
			free(col->buf);
			col->buf = NULL;
			col->alloc_flag = 1;
		}
		else
			(*stack)[0] = '\0';
	}
}

char	*ft_read_line(int fd, char *stack, t_gnl *col)
{
	while (col->flag > 0 && col->ret > 0)
	{
		col->ret = read(fd, col->buf, BUFFER_SIZE);
		if (col->ret < 0)
		{
			free(col->buf);
			free(stack);
			return (NULL);
		}
		else
		{
			col->buf[col->ret] = '\0';
			col->temp = ft_strjoin(stack, col->buf);
			if (!col->temp)
			{
				free(col->buf);
				free(stack);
				return (NULL);
			}
			ft_line_check(&stack, col);
		}
	}
	free(col->buf);
	return (stack);
}

char	*get_next_line(int fd)
{
	static t_colector	sample[MAX_FILES];
	t_gnl				col;

	ft_bzero(&col, sizeof(col));
	col.idx = ft_detect_index(fd, sample);
	if (BUFFER_SIZE <= 0 || fd == -1 || col.idx == -1)
		return (NULL);
	col.ret = 1;
	col.flag = 1;
	ft_alloc_buf_stack(&(sample[col.idx].stack), &col);
	if (col.alloc_flag)
		return (NULL);
	sample[col.idx].stack = ft_read_line(fd, sample[col.idx].stack, &col);
	if (!(sample[col.idx].stack) || sample[col.idx].stack[0] == '\0')
	{
		if (sample[col.idx].stack)
			free(sample[col.idx].stack);
		sample[col.idx].stack = NULL;
		return (NULL);
	}
	col.temp = NULL;
	return (ft_write_line(&(sample[col.idx].stack), &col));
}
