/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_brute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:59:49 by corellan          #+#    #+#             */
/*   Updated: 2024/01/08 14:46:08 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	ft_strlen_pos(char const *org, int start)
{
	int		i;
	int		flag;
	char	*str;

	i = 0;
	flag = NORMAL;
	str = (char *)org + i + start;
	while (*str != '\0')
	{
		flag = ft_flag_identifier(str, flag);
		if (((flag == NORMAL) && (!ft_isspace(*str) && *str != 0) && \
			(ft_isspace(*(str + 1)) || !*(str + 1) || *(str + 1) == 39 || \
			*(str + 1) == 34)) || ((flag == ENDSINGLE) && (*str == 39)) || \
			((flag == ENDDOUBLE) && (*str == 34)) || ((flag == SINGLE || \
			flag == DOUBLE) && (!*(str + 1))))
			break ;
		i++;
		str++;
	}
	if (*str != '\0')
		i++;
	return (i);
}

static size_t	ft_words(char const *str)
{
	size_t	i;
	t_token	flag;

	i = 0;
	flag = NORMAL;
	while (*str)
	{
		flag = ft_flag_identifier(str, flag);
		if (((flag == NORMAL) && (!ft_isspace(*str) && *str != 0) && \
			(ft_isspace(*(str + 1)) || !*(str + 1) || *(str + 1) == 39 || \
			*(str + 1) == 34)) || ((flag == ENDSINGLE) && (*str == 39)) || \
			((flag == ENDDOUBLE) && (*str == 34)) || ((flag == SINGLE || \
			flag == DOUBLE) && (!*(str + 1))))
		{
			i++;
			flag = NORMAL;
		}
		str++;
	}
	return (i);
}

char	**ft_get_brute(char *str)
{
	char	**split;
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.words = ft_words(str);
	split = (char **)malloc(sizeof(char *) * (data.words + 1));
	if (!split)
		return (NULL);
	split[data.words] = NULL;
	while (data.i < data.words)
	{
		data.index = ft_index_after_char(str, data.index);
		data.length = ft_strlen_pos(str, data.index);
		split[data.i] = ft_substr(str, data.index, data.length);
		if (!split[data.i])
		{
			ft_free_split(split);
			return (NULL);
		}
		data.index += data.length;
		(data.i)++;
	}
	return (split);
}
