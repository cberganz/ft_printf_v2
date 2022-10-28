# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 14:38:12 by cberganz          #+#    #+#              #
#    Updated: 2021/12/02 15:37:14 by cberganz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h

SRC =  ft_printf.c			\
		is_arg.c		\
		case_treatment.c	\
		case_text.c		\
		case_c.c		\
		case_s.c		\
		case_i_d.c		\
		case_u.c		\
		case_p.c		\
		case_x.c		\
		case_upperx.c
		
OBJ = $(SRC:.c=.o)
			
CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I.

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
