# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 20:31:00 by jdias-mo          #+#    #+#              #
#    Updated: 2022/06/20 16:24:10 by split            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = main.c philo.c utils.c errors.c

OBJECTS = $(SOURCES:.c=.o)

CC = gcc

CFLAGS = -pthread -Wall -Wextra -Werror

.c.o: $(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) philo.h
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
