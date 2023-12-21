/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:25:36 by corellan          #+#    #+#             */
/*   Updated: 2023/12/20 16:28:51 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*rewrite_strings(t_data *data, char const *original, char *substr)
{
		
}

static char	**process_split(char **array, char *str)
{
	t_data	data;
	t_list	*lst;
	char	*current;

	ft_bzero(&data, sizeof(data));
	lst = NULL;
	current = NULL;
	while (array[data.i])
	{
		data.spaces = ft_index_after_char(str, data.length);
		current = rewrite_strings(&data, str, array[data.i]);
		if (!current)
		{
			ft_lstclear(&lst, &free);
			return (NULL);
		}
	}
}

char	**ft_parser(char *str)
{
	char	**array;

	array = ft_get_split(str);
	if (!array)
		return (NULL);
	array = process_split(array, str);
	if (!array)
		return (NULL);
	return (array);
}