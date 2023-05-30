# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 20:39:26 by mfouadi           #+#    #+#              #
#    Updated: 2023/05/30 23:57:46 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus

CC := cc

SRC :=	main.c \
		utils.c

OBJ := $(patsubst %.c, obj/%.o, $(SRC))

OBJ_DIR := obj/

CFLAGS := -Wall -Werror -Wextra

HEADERS = philosophers_bonus.h

RM := rm -rf

all : $(NAME)
	
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : re clean fclean all

