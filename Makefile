# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:42:39 by cberganz          #+#    #+#              #
#    Updated: 2022/11/08 11:28:24 by cberganz         ###   ########.fr        #
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
			  handlers_1.c							\
			  handlers_2.c							\
			  utils.c

TESTER_NAME	= unit_test/test.c

SRC_DIR		= src/
SRC			= ${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR		= objs/
OBJ_DIRS	= ${sort ${dir ${OBJ}}}
OBJ_NAME	= ${SRC_NAME:.c=.o}
OBJ			= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${LIB_NAME} #${NAME}

${NAME}: ${LIB_NAME}
	${CC} ${FLAGS} ${TESTER_NAME} -o ${NAME} -L. -lftprintf

bonus: ${LIB_NAME}
	#${CC} ${FLAGS} ${TESTER_NAME} -o ${NAME} -L. -lftprintf

${LIB_NAME}: ${OBJ}
	@ar rcs ${LIB_NAME} ${OBJ}

${OBJ_DIRS}:
	@mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${FLAGS} -I${INCLUDE} -c $< -o $@

benchmark: all
	gcc benchmark/benchmark.c -I./include/ -L. -lftprintf -o newVersion
	mv newVersion benchmark/newVersion
	hyperfine './benchmark/newVersion' './benchmark/oldVersion'

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${LIB_NAME}
	rm -f ${NAME}

re: fclean all

.PHONY : all clean fclean test re
