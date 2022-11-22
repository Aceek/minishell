# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 15:08:45 by pbeheyt           #+#    #+#              #
#    Updated: 2022/11/22 06:13:21 by pbeheyt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lexer

SRC		= main.c \
		env.c \
		lexer.c \
		libft1.c \
		libft2.c \
		libft3.c \
		libft4.c \
		libft5.c \
		parser.c \
		redir.c \

HEAD	= -I include

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror -g 

OBJS 	= ${SRC:.c=.o} 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline


.c.o:
	${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
