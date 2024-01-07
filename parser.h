/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:24:00 by corellan          #+#    #+#             */
/*   Updated: 2024/01/08 01:32:11 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

typedef enum e_token
{
	NORMAL,
	SINGLE,
	ENDSINGLE,
	DOUBLE,
	ENDDOUBLE,
	SLASH,
	SLASHDQUOTE
}	t_token;

typedef struct s_data
{
	size_t	i;
	size_t	index;
	size_t	words;
	size_t	length;
	size_t	spaces;
}	t_data;

typedef struct s_parser
{
	char	*original_cmd;
	char	*temp_str;
	char	**brute_cmd;
	int		error_flag;
	size_t	idx;
	size_t	spaces;
	size_t	len;
	t_list	*tmp;
	t_list	*cmd_lst;
	t_token	flags[2];
	t_token	tok;
}	t_parser;

char	**ft_get_brute(char *str);
t_token	ft_flag_identifier(char const *str, t_token flag);
size_t	ft_index_after_char(char *str, size_t pos);
void	get_flags(t_parser *parser, char const *str);
size_t	get_size_alloc(t_parser *parser, char *str);
void	clean_extra_char(char **result, char const *src, t_parser *parser);
char	**parser_free_error(t_parser *parser);
void	parser_free_interface(t_parser *parser);

#endif