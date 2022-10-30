/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/30 21:57:09 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

static const uint8_t	g_flags_map[128] =
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	16,	0,	0,	8,	0,	64,	0,	0,
	0,	0,	0,	32,	0,	1,	4,	0,	2,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	64,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	64,
	64,	0,	0,	0,	0,	64,	0,	0,	0,	0,
	0,	0,	64,	0,	0,	64,	0,	64,	0,	0,
	64,	0,	0,	0,	0,	0,	0,	0
};

char	*init(const char **s)
{
	if (g_flags_map[*++(*s)] & B_FORMAT_SPECIFIER) // error with ++ here: it jumps the format specifier at end
		return (this->_current);
	if (g_flags_map[**s])
	{
		this->flags.flags |= g_flags_map[**s];
		if (g_flags_map[**s] & B_DOT_FLAG)
			while (isdigit(**s))
				this->flags.prec = this->flags.prec * 10 + *(*s)++ - '0';
	}
	else if (isdigit(**s))
	{
		while (isdigit(**s))
			this->flags.width = this->flags.width * 10 + *(*s)++ - '0';
		*(*s)--;
	}
	init(s);
}

void	reset(void)
{
	this->flags.flags = B_RESET;
	this->flags.width = 0;
	this->flags.prec = 0;
	this->_save_current = NULL;
}

bool	is_flag_set(uint16_t flag)
{
	return (this->flags.flags & flag);
}

void	print_flags(void)
{
	printf("flags | B_MINUS_FLAG : %d\n", this->flags.is_flag_set(B_MINUS_FLAG));
	printf("flags | B_ZERO_FLAG : %d\n", this->flags.is_flag_set(B_ZERO_FLAG));
	printf("flags | B_DOT_FLAG : %d\n", this->flags.is_flag_set(B_DOT_FLAG));
	printf("flags | B_HASHTAG_FLAG : %d\n", this->flags.is_flag_set(B_HASHTAG_FLAG));
	printf("flags | B_SPACE_FLAG : %d\n", this->flags.is_flag_set(B_SPACE_FLAG));
	printf("flags | B_PLUS_FLAG : %d\n", this->flags.is_flag_set(B_PLUS_FLAG));
	printf("flags | FORMAT_IDENTIFIER : %d\n", this->flags.flags & B_FORMAT_SPECIFIER);
	printf("flags | FIELD_WIDTH : %d\n", this->flags.width);
	printf("flags | PRECISION : %d\n", this->flags.prec);
}

void	flags_construct(void)
{
	this->flags.init = &init;
	this->flags.reset = &reset;
	this->flags.is_flag_set = &is_flag_set;
	this->flags.print_flags = &print_flags;
}
