# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 20:31:00 by jdias-mo          #+#    #+#              #
#    Updated: 2023/01/25 15:19:18 by jdias-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRC =		$(addsuffix .c,	main \
							philo \
							utils \
							errors)

INC_DIR =	inc/

SRC_DIR =	src/

OBJ_DIR =	obj/

INC =		-I$(INC_DIR)

OBJ =		$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

CC =		gcc

CFLAGS =	-pthread -Wall -Wextra -Werror

RM =		rm -f

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $(<) -o $(@) $(INC)

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(NAME):		$(OBJ_DIR) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
				$(RM) $(OBJ) -r $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
