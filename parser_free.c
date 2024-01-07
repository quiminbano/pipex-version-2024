/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:19:49 by corellan          #+#    #+#             */
/*   Updated: 2024/01/08 01:27:00 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
