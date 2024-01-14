/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:06:31 by corellan          #+#    #+#             */
/*   Updated: 2024/01/14 11:27:10 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char const *str1, char const *str2)
{
	size_t	i;
	int		s1;
	int		s2;

	i = 0;
	while ((str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0'))
		i++;
	s1 = (unsigned const char)str1[i];
	s2 = (unsigned const char)str2[i];
	if (s1 == s2)
		return (0);
	else
		return (s1 - s2);
}
