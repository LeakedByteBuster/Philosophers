# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 19:26:42 by mfouadi           #+#    #+#              #
#    Updated: 2023/04/28 22:29:08 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  := philo

CC := cc

CFLAGS := -Wall -Werror -Wextra #-fsanitize=address

SRC :=	main.c \
		utils.c

OBJ_DIR := obj

OBJ = $(patsubst %, $(OBJ_DIR)/%, $(SRC:.c=.o))

HEADERS := inc

RM := rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c $(HEADERS)
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

.SILENT : re fclean clean all
