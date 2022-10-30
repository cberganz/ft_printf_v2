# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/10/30 21:11:08 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

LIB_NAME	= libftprintf.a

CC			= gcc

INCLUDE		= include/

FLAGS		= -g3#-Wall -Wextra -Werror -g

SRC_NAME	= Flags.c								\
			  Printer.c								\
			  ft_printf.c							\
			  handlers/bufferize_string.c			\
			  handlers/handle_illegal_argument.c	\
			  handlers/handle_char.c				\
			  handlers/handle_string.c				\
			  handlers/handle_percent.c				\
			  handlers/handle_decimal.c				\
			  handlers/handle_pointer.c				\
			  handlers/handle_unsigned.c			\
			  handlers/handle_hexadecimal_lower.c	\
			  handlers/handle_hexadecimal_upper.c

TESTER_NAME	= unit_test/test.c

SRC_DIR		= src/
SRC			= ${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR		= objs/
OBJ_DIRS	= ${sort ${dir ${OBJ}}}
OBJ_NAME	= ${SRC_NAME:.c=.o}
OBJ			= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${LIB_NAME} ${NAME}

${NAME}: ${LIB_NAME}
	${CC} ${FLAGS} ${TESTER_NAME} -o ${NAME} -L. -lftprintf

bonus: ${LIB_NAME}
	${CC} ${FLAGS} ${TESTER_NAME} -o ${NAME} -L. -lftprintf

${LIB_NAME}: ${OBJ}
	@ar rcs ${LIB_NAME} ${OBJ}

${OBJ_DIRS}:
	@mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${FLAGS} -I${INCLUDE} -c $< -o $@

benchmark: all
	@bash unit_test/benchmark/benchmark.sh

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${LIB_NAME}
	rm -f ${NAME}

re: fclean all

.PHONY : all clean fclean test re
