/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:04:49 by corellan          #+#    #+#             */
/*   Updated: 2023/11/27 13:40:09 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_int_ar(int	**array, int ammount)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < ammount)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}
