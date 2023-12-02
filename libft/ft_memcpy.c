/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:54:26 by corellan          #+#    #+#             */
/*   Updated: 2023/10/27 22:19:40 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tempdest;
	unsigned const char	*tempsrc;

	i = 0;
	tempdest = (unsigned char *)dest;
	tempsrc = (unsigned const char *)src;
	if (tempdest == NULL && tempsrc == NULL)
		return (NULL);
	while (i < n)
	{
		tempdest[i] = tempsrc[i];
		i++;
	}
	return (dest);
}
