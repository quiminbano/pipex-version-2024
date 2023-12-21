/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:24:00 by corellan          #+#    #+#             */
/*   Updated: 2023/12/09 23:13:07 by corellan         ###   ########.fr       */
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
	int		fbefore;
	int		fafter;
}	t_data;

char	**ft_get_split(char *str);
int		ft_flag_identifier(char const *str, int flag);
size_t	ft_index_after_char(char *str, size_t pos);

#endif