/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:40:46 by corellan          #+#    #+#             */
/*   Updated: 2023/11/14 17:44:04 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*s;
	size_t	alloc_max;

	alloc_max = ((size_t)1 << 31);
	if ((nitems > 0) && (size > 0))
	{
		if ((((nitems * size) % size) != 0) || \
			(((nitems * size) % nitems) != 0))
			return (NULL);
	}
	if ((nitems * size) > alloc_max)
		return (NULL);
	s = (void *)malloc(size * nitems);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, (nitems * size));
	return (s);
}
