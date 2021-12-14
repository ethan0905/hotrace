# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 10:59:26 by esafar            #+#    #+#              #
#    Updated: 2021/12/12 20:58:19 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = hotrace

SRCS = main.c \
		./read_input.c \
		./parse_input.c \
		./write_to_buf.c \
		./insert.c \
		./find.c \
		./utils.c

CC = cc

FLAGS = -Wextra -Werror -Wall -O3 -fno-builtin

OBJS = ${SRCS:.c=.o}

.c.o:
	@printf "${LIGHT_BLUE}=>	"
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
	@printf "${NC}"

all: ${NAME}

${NAME}: ${OBJS}
	cc ${FLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS} 

fclean:
	rm -f ${NAME} ${OBJS}

re: fclean all
