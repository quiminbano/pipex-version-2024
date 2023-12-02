/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:41:57 by corellan          #+#    #+#             */
/*   Updated: 2023/10/22 09:13:58 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned const char		*s;
	unsigned char			*d;
	size_t					l;	

	s = (unsigned const char *)src;
	d = (unsigned char *)dest;
	l = n;
	if (s == NULL && d == NULL)
		return (NULL);
	if (d > s)
	{
		while (l > 0)
		{
			d[l - 1] = s[l - 1];
			l--;
		}
		return ((unsigned char *)d);
	}
	else
	{
		return (ft_memcpy(dest, src, n));
	}
}
