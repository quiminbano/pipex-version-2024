/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_brute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:59:49 by corellan          #+#    #+#             */
/*   Updated: 2024/01/12 13:42:39 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	ft_strlen_pos(char const *org, size_t start, t_data *data)
{
	size_t	i;
	char	*str;

	i = 0;
	data->flag = NORMAL;
	data->prev_flag = NORMAL;
	str = (char *)org + i + start;
	while (*str != '\0')
	{
		data->prev_flag = data->flag;
		data->flag = ft_flag_identifier(str, data->flag);
		if (((data->flag == NORMAL) && ((data->prev_flag == SLASH && \
			*str != 0) || (!ft_isspace(*str) && *str != 0)) && \
			(ft_isspace(*(str + 1)) || !*(str + 1) || *(str + 1) == 39 || \
			*(str + 1) == 34)) || ((data->flag == ENDSINGLE) && \
			(*str == 39)) || ((data->flag == ENDDOUBLE) && (*str == 34)) || \
			((data->flag == SINGLE || data->flag == DOUBLE || \
			data->flag == SLASH) && (!*(str + 1))))
			break ;
		i++;
		str++;
	}
	if (*str != '\0')
		i++;
	return (i);
}

static size_t	ft_words(char const *str, t_data *data)
{
	size_t	i;

	i = 0;
	data->flag = NORMAL;
	data->prev_flag = NORMAL;
	while (*str)
	{
		data->prev_flag = data->flag;
		data->flag = ft_flag_identifier(str, data->flag);
		if (((data->flag == NORMAL) && ((data->prev_flag == SLASH && \
			*str != 0) || (!ft_isspace(*str) && *str != 0)) && \
			(ft_isspace(*(str + 1)) || !*(str + 1) || *(str + 1) == 39 || \
			*(str + 1) == 34)) || ((data->flag == ENDSINGLE) && \
			(*str == 39)) || ((data->flag == ENDDOUBLE) && (*str == 34)) || \
			((data->flag == SINGLE || data->flag == DOUBLE || \
			data->flag == SLASH) && (!*(str + 1))))
		{
			i++;
			data->flag = NORMAL;
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
	data.words = ft_words(str, &data);
	split = (char **)malloc(sizeof(char *) * (data.words + 1));
	if (!split)
		return (NULL);
	split[data.words] = NULL;
	while (data.i < data.words)
	{
		data.index = ft_index_after_char(str, data.index);
		data.length = ft_strlen_pos(str, data.index, &data);
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
