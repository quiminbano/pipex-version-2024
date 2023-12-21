/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:58:51 by corellan          #+#    #+#             */
/*   Updated: 2023/12/21 15:25:04 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_in_env(char **envp, char *needle)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(envp[i], needle, ft_strlen(needle)))
		i++;
	return (i);
}
