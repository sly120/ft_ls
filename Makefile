# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sly <sly@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/13 21:00:43 by sly               #+#    #+#              #
#    Updated: 2015/03/21 19:50:54 by sly              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC_PATH = ./src/
SRC_NAME = $(shell ls $(SRC_PATH) | grep "\.c")
OBJ_PATH = ./obj/
INC_PATH = ./include/
LIB_PATH = ./libft/
LIB_NAME = -lft
AR = ar rc
CC = cc
CFLAGS += -Wall -Wextra -Werror
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIBOPTION = $(addprefix -L , $(LIB_PATH))
INC = $(addprefix -I , $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ) $(LIB_NAME)
	$(CC) $(LIBOPTION) $(LIBFT_NAME) $(INC) -o $(NAME) $(LIB_NAME) $(OBJ)

$(LIB_NAME): libfclean
	make -C libft

libfclean:
	make -C libft/ fclean

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(INC) -o $@ -c $<

.PHONY: clean $(LIB_NAME) fclean all re norme libfclean

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean libfclean
	rm -fv $(NAME)

re: fclean
	make

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h
