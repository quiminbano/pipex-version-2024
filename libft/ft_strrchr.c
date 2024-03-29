/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:16:14 by corellan          #+#    #+#             */
/*   Updated: 2023/10/22 09:15:05 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				len;
	int				i;
	unsigned char	d;

	i = 0;
	len = ft_strlen(str);
	d = (unsigned char)c;
	while ((len >= 0) && (str[len] != d))
	{
		len--;
	}
	while (i < len)
	{
		str++;
		i++;
	}
	if (len < 0)
		return (0);
	else
		return ((char *)str);
}
