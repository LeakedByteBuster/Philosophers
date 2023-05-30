# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 19:26:42 by mfouadi           #+#    #+#              #
#    Updated: 2023/05/30 04:46:46 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  := philo

CC := cc

CFLAGS := -Wall -Werror -Wextra

SRC :=	src/main.c \
		src/utils.c \
		src/routine.c \
		src/initialize_simulation.c \
		

OBJ_DIR := obj

OBJ = $(patsubst %, $(OBJ_DIR)/%, $(SRC:.c=.o))

HEADERS_DIR := inc

HEADERS_FILE := inc/philosophers.h

RM := rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $(NAME) 

$(OBJ_DIR)/%.o : %.c $(HEADERS_FILE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(HEADERS_DIR) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

.SILENT : re fclean clean all
