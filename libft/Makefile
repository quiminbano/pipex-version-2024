# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 12:00:04 by corellan          #+#    #+#              #
#    Updated: 2024/01/14 11:30:23 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_free_split.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_split_length.c \
ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRC_B = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c \
ft_lstnew_bonus.c ft_lstsize_bonus.c

GNL_SRC = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)

GNL_OUT = $(GNL_SRC:.c=.o)

OUT = $(SRC:.c=.o)

OUT_B = $(SRC_B:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

all: $(NAME)

$(NAME): $(OUT) $(GNL_OUT)
		ar rcs $(NAME) $(OUT) $(GNL_OUT)

bonus: .bonus

.bonus: $(OUT_B) $(OUT) $(GNL_OUT)
		ar rus $(NAME) $(OUT) $(OUT_B) $(GNL_OUT)
		@touch .bonus

%.o: %.c
		$(CC) $(FLAGS) -I. -c $< -o $@

clean:
		rm -f $(OUT) $(OUT_B) $(GNL_OUT)
		@rm -f .bonus

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean