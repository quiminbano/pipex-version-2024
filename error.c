/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:39:11 by corellan          #+#    #+#             */
/*   Updated: 2023/09/03 19:57:28 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error, char *str, int err)
{
	ft_putendl_fd("pipex: ", 2);
	ft_putend_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (error == OPENIN || error == OPENOUT)
		ft_putendl_fd(strerror(2), 2);
}
