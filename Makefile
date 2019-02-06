# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rostroh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 15:17:16 by rostroh           #+#    #+#              #
#    Updated: 2019/02/05 23:24:00 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
	  src/malloc.c \
	  src/tiny.c \
	  src/show.c \
	  src/small.c

LIB_FT = ./libft/libft.a

LIB_PRINTF = ./libft/src/printf/libftprintf.a

FLG = -Wall -Werror -Wextra -lncurses

NAME = malloc

all: $(NAME)

$(NAME): $(SRC) $(SRC_MD5) $(SRC_SHA256)
	make -C ./libft
	gcc $(FLAG) -o $(NAME) $(SRC) -I includes $(LIB_FT) $(LIB_PRINTF)

clean:
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all
