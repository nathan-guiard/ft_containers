# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/14 11:00:15 by nguiard           #+#    #+#              #
#    Updated: 2022/11/13 15:00:07 by nguiard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL:= /bin/zsh

SRC =	main.cpp		\

CC = c++ -g3

OBJ = ${SRC:.cpp=.o}

DEP = ${SRC:.cpp=.d}

NAME = test

FLAGS := -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address

.cpp.o:
	${CC} ${FLAGS} -MMD -c $< -o ${<:.cpp=.o}

${NAME}: ${OBJ}
	${CC} ${OBJ} ${FLAGS} -o ${NAME}

all: ${NAME}

-include ${DEP}

clean:
	rm -rf ${OBJ}

fclean:
	rm -rf ${OBJ} ${NAME}

re: fclean all

.PHONY: all fclean clean re
