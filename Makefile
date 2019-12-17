# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rostroh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 11:17:25 by rostroh           #+#    #+#              #
#    Updated: 2019/12/17 14:44:03 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc$(HOSTTYPE).so

SRC = malloc.c

OBJ = $(SRC:.c=.o)

SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./include

SRCS = $(SRC:%=$(SRC_DIR)/%)
OBJS = $(OBJ:%=$(OBJ_DIR)/%)

LIBFT = libft.a
LIB_DIR = ./libft
LFT = $(LIB_DIR)/$(LIBFT)
LIB = -L $(LIB_DIR) -l$(LIBFT:lib%.a=%)

FLG = -Wall \
	  -Werror \
	  -Wextra

CC = gcc

all:
	@make -C $(LIB_DIR)
	@make $(NAME)

$(OBJS): $(SRCS)
	@mkdir -p $(OBJ_DIR)
	gcc $(FLG) -I $(INC_DIR) -o $@ -c -fPIC $<
	@echo "fin de compilation"

$(NAME): $(OBJS)
	@echo "creat lib"
	$(CC) $(FLG) $< $(LFT) -shared -o $@ $(LIB)

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -rf $(NAME)

re: fclean all

print-%:
	@echo $*=$($*)
