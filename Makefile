# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 14:06:32 by corellan          #+#    #+#              #
#    Updated: 2024/01/27 09:23:17 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c pipex_utils.c find_path.c error.c execution.c

SRC_BONUS = pipex_bonus.c pipex_utils_bonus.c find_path_bonus.c error_bonus.c \
execution_bonus.c heredoc_bonus.c

PAR = parser.c get_brute.c parser_utils.c parser_utils_extra.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

OBJ_PAR = $(PAR:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_PAR)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ) $(OBJ_PAR) $(LIBFT) -o $(NAME)

bonus: .bonus

.bonus: $(OBJ_BONUS) $(OBJ_PAR)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ_BONUS) $(OBJ_PAR) $(LIBFT) -o $(NAME)
		@touch .bonus

%.o: %.c
		$(CC) $(FLAGS) -I. -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_PAR)
		@rm -f .bonus

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus