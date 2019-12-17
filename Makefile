# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rostroh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 11:17:25 by rostroh           #+#    #+#              #
#    Updated: 2019/12/17 19:37:07 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc$(HOSTTYPE).so

SRC = malloc.c area.c creat_area.c tools.c

OBJ = $(SRC:.c=.o)

SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./include

OBJS = $(OBJ:%=$(OBJ_DIR)/%)

LIBFT = libft.a
LIB_DIR = ./libft
LFT = $(LIB_DIR)/$(LIBFT)
LIB = -L $(LIB_DIR) -l$(LIBFT:lib%.a=%)

OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

FLG = -Wall -Werror -Wextra

CC = gcc

all:
	@make -C $(LIB_DIR)
	@make $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLG) -I $(INC_DIR) -o $@ -c -fPIC $<
	@echo "fin de compilation"

$(NAME): $(OBJS)
	@echo "creat lib"
	$(CC) $(FLG) $(OBJS) $(LFT) -shared -o $@ $(LIB)
	ln -fs $(NAME) libft_malloc.so

clean:
	@rm -rf $(OBJ_DIR)
	@make $@ -C $(LIB_DIR)

fclean:
	@rm -rf $(NAME)
	@make $@ -C $(LIB_DIR)

re: fclean all

print-%:
	@echo $*=$($*)
