/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:02:32 by corellan          #+#    #+#             */
/*   Updated: 2024/01/08 12:40:35 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_flags(t_parser *parser, char const *str)
{
	size_t	i;

	i = 0;
	parser->tok = NORMAL;
	while (str[i])
	{
		parser->tok = ft_flag_identifier(str + i, parser->tok);
		if (!i)
			parser->flags[0] = parser->tok;
		else if (!str[i + 1])
			parser->flags[1] = parser->tok;
		i++;
	}
}

void	clean_extra_char(char **result, char const *src, t_parser *parser)
{
	char	*temp;
	t_token	system;

	temp = (*result);
	if ((parser->flags[0] == DOUBLE && parser->flags[1] == ENDDOUBLE))
		system = DOUBLE;
	else if ((parser->flags[0] == SINGLE && parser->flags[1] == ENDSINGLE))
		system = SINGLE;
	else
		system = NORMAL;
	while (*src)
	{
		if ((system == DOUBLE && *src != 34) || (system == SINGLE && \
			*src != 39) || (system == NORMAL && *src != 92))
		{
			if (system == DOUBLE && *src == 92 && *(src + 1) == 34)
				*temp = *(src + 1);
			else
				*temp = *src;
			temp++;
		}
		src++;
	}
	(*temp) = '\0';
}

size_t	get_size_alloc(t_parser *parser, char *str)
{
	size_t	i;
	t_token	system;

	i = 0;
	if ((parser->flags[0] == DOUBLE && parser->flags[1] == ENDDOUBLE))
		system = DOUBLE;
	else if ((parser->flags[0] == SINGLE && parser->flags[1] == ENDSINGLE))
		system = SINGLE;
	else
		system = NORMAL;
	while (str[i])
	{
		if ((system == DOUBLE && str[i] == 34) || (system == SINGLE && \
			str[i] == 39) || (system == NORMAL && str[i] == 92))
			parser->len -= 1;
		i++;
	}
	return (parser->len);
}

t_token	ft_flag_identifier(char const *str, t_token flag)
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
	else if ((flag == NORMAL) && (*str == 92))
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
	while (ft_isspace(str[i + pos]) && str[i + pos])
		i++;
	return (i + pos);
}
