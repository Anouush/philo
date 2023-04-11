# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 18:54:59 by angalsty          #+#    #+#              #
#    Updated: 2023/04/03 18:57:28 by angalsty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC = philo.h

SRCS = main.c init.c utils.c thread_init.c routine.c monitor.c

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I. -pthread 

.c.o:
	${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
