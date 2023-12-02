/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:24:00 by corellan          #+#    #+#             */
/*   Updated: 2023/11/27 13:33:59 by corellan         ###   ########.fr       */
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
	int	i;
	int	index;
	int	words;
	int	length;
}	t_data;

char	**ft_parser(char *str);

#endif