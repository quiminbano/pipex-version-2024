/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:59:41 by corellan          #+#    #+#             */
/*   Updated: 2023/10/22 09:14:30 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	int				l;
	unsigned char	d;

	i = 0;
	l = ft_strlen(str);
	d = (unsigned char)c;
	while (*str != d && *str != '\0')
	{
		str++;
		i++;
	}
	if (i == l && d != '\0')
		return (0);
	else
		return ((char *)str);
}
