# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 10:38:47 by mprofett          #+#    #+#              #
#    Updated: 2023/12/20 13:58:23 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ./PmergeMe

SRC			= main.cpp PmergeMe.cpp

OBJ			= ${SRC:.cpp=.o}

CC			= c++

RM			= rm -rf

CPPFLAGS	= -g -Wall -Wextra -Werror -std=c++98

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CPPFLAGS} ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
