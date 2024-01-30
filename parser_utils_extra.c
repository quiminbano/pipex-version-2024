/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:19:49 by corellan          #+#    #+#             */
/*   Updated: 2024/01/30 22:37:41 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_slash(char const *str)
{
	static int	flag = 0;
	int			return_value;

	return_value = 0;
	if (flag == 0 && *str == 92)
	{
		return_value = 1;
		flag = 1;
	}
	else if ((flag == 1 && *str == 92) || *str != 92)
	{
		return_value = 0;
		flag = 0;
	}
	if (*(str + 1) != 92)
		flag = 0;
	return (return_value);
}

void	parser_free_interface(t_parser *parser)
{
	if (parser->brute_cmd)
	{
		ft_free_split(parser->brute_cmd);
		parser->brute_cmd = NULL;
	}
	if (parser->cmd_lst)
	{
		ft_lstclear(&(parser->cmd_lst), &free);
		parser->cmd_lst = NULL;
	}
}

char	**parser_free_error(t_parser *parser)
{
	parser_free_interface(parser);
	return (NULL);
}
