/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:02:32 by corellan          #+#    #+#             */
/*   Updated: 2023/12/09 22:53:00 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_flag_identifier(char const *str, int flag)
{
	if ((flag == NORMAL) && (*str == 39))
		return (SINGLE);
	else if ((flag == SINGLE) && (*str == 39))
		return (ENDSINGLE);
	else if ((flag == NORMAL) && (*str == 34))
		return (DOUBLE);
	else if ((flag == DOUBLE) && (*str == 34))
		return (ENDDOUBLE);
	else if ((flag == DOUBLE) && *str == 92)
		return (SLASHDQUOTE);
	else if ((flag == NORMAL) && (*str == 92) && (*(str + 1) == 34 || \
		*(str + 1) == 39))
		return (SLASH);
	else if (flag == SLASH)
		return (NORMAL);
	else if (flag == SLASHDQUOTE)
		return (DOUBLE);
	return (flag);
}

size_t	ft_index_after_char(char *str, size_t pos)
{
	size_t	i;

	i = 0;
	while (str[i + pos] == 32 && str[i + pos])
		i++;
	return (i + pos);
}
