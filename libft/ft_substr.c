/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:32:55 by corellan          #+#    #+#             */
/*   Updated: 2023/10/22 10:11:56 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_write_str(char const *s, char *dest, size_t st, size_t len)
{
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen(s);
	if (st >= l)
	{
		dest[0] = '\0';
		return (dest);
	}
	while (i < len && st < l)
	{
		dest[i] = s[st];
		i++;
		st++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*dest;
	size_t	l;

	l = ft_strlen(s);
	if (start >= l)
		dest = (char *)malloc(sizeof(char) * (1));
	else if (len <= l && (l - start) >= len)
		dest = (char *)malloc(sizeof(char) * (len + 1));
	else
		dest = (char *)malloc(sizeof(char) * ((l - start) + 1));
	if (dest == NULL || s == NULL)
		return (NULL);
	return (ft_write_str(s, dest, start, len));
}
