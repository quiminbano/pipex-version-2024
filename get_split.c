/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:59:49 by corellan          #+#    #+#             */
/*   Updated: 2023/12/02 14:38:09 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_flag_identifier(char const *str, int flag)
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

static int	ft_strlen_pos(char const *org, int start)
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
		if (((flag == NORMAL) && (*str != 32 && *str != 0) && \
			(*(str + 1) == 32 || !*(str + 1) || *(str + 1) == 39 || \
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

static int	ft_index_after_char(char *str, int pos)
{
	int	i;

	i = 0;
	while (str[i + pos] == 32)
		i++;
	return (i + pos);
}

static int	ft_words(char const *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = NORMAL;
	while (*str != '\0')
	{
		flag = ft_flag_identifier(str, flag);
		if (((flag == NORMAL) && (*str != 32 && *str != 0) && \
			(*(str + 1) == 32 || !*(str + 1) || *(str + 1) == 39 || \
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

char	**ft_get_split(char *str)
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
		split[data.i] = ft_substr(str, (int)data.index, (int)data.length);
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
