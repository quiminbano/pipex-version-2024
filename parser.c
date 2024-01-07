/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:25:36 by corellan          #+#    #+#             */
/*   Updated: 2024/01/08 01:32:46 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**return_polished_array(t_parser *parser)
{
	size_t	size_lst;
	t_list	*iter;
	size_t	i;
	char	**array;

	size_lst = (size_t)ft_lstsize(parser->cmd_lst);
	array = (char **)malloc(sizeof(char *) * (size_lst + 1));
	if (!array)
		return (NULL);
	iter = parser->cmd_lst;
	i = 0;
	array[size_lst] = NULL;
	while (i < size_lst)
	{
		array[i] = ft_strdup((char *)iter->content);
		if (!array[i])
		{
			ft_free_split(array);
			array = NULL;
			return (NULL);
		}
		i++;
		iter = iter->next;
	}
	return (array);
}

static void	append_to_last(char **result, t_parser *parser)
{
	char	*content;

	content = NULL;
	content = (char *)ft_lstlast(parser->cmd_lst)->content;
	parser->temp_str = ft_strjoin(content, (*result));
	if (!parser->temp_str)
	{
		parser->error_flag = 1;
		free(*result);
		(*result) = NULL;
		return ;
	}
	ft_lstdelone(ft_lstlast(parser->cmd_lst), &free);
	free(*result);
	(*result) = NULL;
	(*result) = parser->temp_str;
	parser->temp_str = NULL;
}

static void	polish_cmd_add_lst(t_parser *parser, char *str)
{
	char	*result;
	size_t	size_alloc;

	result = NULL;
	size_alloc = get_size_alloc(parser, str);
	result = (char *)malloc(sizeof(char) * (size_alloc + 1));
	if (!result)
	{
		parser->error_flag = 1;
		return ;
	}
	clean_extra_char(&result, str, parser);
	if (parser->idx && !parser->spaces)
		append_to_last(&result, parser);
	if (!parser->error_flag)
	{
		parser->tmp = ft_lstnew(result);
		if (!parser->tmp)
		{
			parser->error_flag = 1;
			free(result);
			return ;
		}
		ft_lstadd_back(&parser->cmd_lst, parser->tmp);
	}
}

static char	**process_brute(t_parser *parser)
{
	size_t	i;

	i = 0;
	while (parser->brute_cmd[parser->idx])
	{
		parser->tmp = NULL;
		parser->spaces = ft_index_after_char(parser->original_cmd, i);
		i = parser->spaces;
		ft_bzero(&parser->flags, (sizeof(t_token) * 2));
		get_flags(parser, parser->brute_cmd[parser->idx]);
		parser->len = ft_strlen(parser->brute_cmd[parser->idx]);
		i += parser->len;
		polish_cmd_add_lst(parser, parser->brute_cmd[parser->idx]);
		if (parser->error_flag)
			return (parser_free_error(parser));
		(parser->idx)++;
	}
	return (return_polished_array(parser));
}

char	**ft_parser(char *str)
{
	char		**array;
	t_parser	parser;

	ft_bzero(&parser, sizeof(parser));
	parser.brute_cmd = ft_get_brute(str);
	if (!parser.brute_cmd)
		return (NULL);
	parser.original_cmd = str;
	array = process_brute(&parser);
	if (!array)
		return (parser_free_error(&parser));
	parser_free_interface(&parser);
	return (array);
}
