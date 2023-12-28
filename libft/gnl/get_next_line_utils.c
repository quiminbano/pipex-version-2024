/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:02:53 by corellan          #+#    #+#             */
/*   Updated: 2023/12/28 21:34:03 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_detect_index(int fd, t_colector *sample)
{
	int	i;

	i = 0;
	if (fd == 0)
		return (i);
	else
	{
		if (sample[0].fds == 0)
			i++;
		while (i < MAX_FILES && sample[i].fds != 0)
		{
			if (sample[i].fds == fd)
				return (i);
			i++;
		}
		if (i == MAX_FILES)
			return (-1);
		sample[i].fds = fd;
		return (i);
	}
}
