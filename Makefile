# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 14:06:32 by corellan          #+#    #+#              #
#    Updated: 2024/01/04 17:24:31 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c pipex_utils.c find_path.c error.c execution.c

SRC_BONUS = pipex_bonus.c pipex_utils_bonus.c find_path_bonus.c error_bonus.c \
execution_bonus.c heredoc_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

LIBFT = -Llibft -lft

CC = cc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ):
		$(CC) $(FLAGS) -I. -Ilibft -c $(SRC)

bonus: .bonus

.bonus: $(OBJ_BONUS)
		$(MAKE) bonus -C ./libft
		$(CC) $(FLAGS) -I. -Ilibft $(OBJ_BONUS) $(LIBFT) -o $(NAME)
		@touch .bonus

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ) $(OBJ_BONUS)
		@rm -f .bonus

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus