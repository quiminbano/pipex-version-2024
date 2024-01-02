# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 14:06:32 by corellan          #+#    #+#              #
#    Updated: 2024/01/02 18:24:53 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c pipex_utils.c find_path.c error.c execution.c

OBJ = $(SRC:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ):
		$(CC) $(FLAGS) -I. -Ilibft -c $(SRC)

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean