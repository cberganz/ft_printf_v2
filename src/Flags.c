/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/27 03:23:05 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static Flags	*flags_singleton(void)
{
	static Flags	obj;

	return (&obj);
}
#define this flags_singleton()

static const uint16_t b_map[128] = 
{
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		16,		0,		0,		8,		0,		1<<8,	0,		0,
	0,		0,		0,		32,		0,		1,		4,		0,		2,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		9<<8,	0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		2<<8,
	5<<8,	0,		0,		0,		0,		6<<8,	0,		0,		0,		0,
	0,		0,		4<<8,	0,		0,		3<<8,	0,		7<<8,	0,		0,
	8<<8,	0,		0,		0,		0,		0,		0,		0
};		

static void	init(const char **s)
{
	while (!(b_map[*(*s + 1)] & B_FORMAT_SPECIFIER))
	{
		if (b_map[*(*s + 1)] & B_FLAG_SPECIFIERS)
		{
			this->flags |= b_map[*++(*s)];
			if (b_map[**s] & B_DOT_FLAG)
				while (isdigit(*(*s + 1)))
					this->precision = this->precision * 10 + *++(*s) - '0';
		}
		else if (isdigit(*(*s + 1)))
			while (isdigit(*(*s + 1)))
				this->field_width = this->field_width * 10 + *++(*s) - '0';
		else
			*(*s)++;
	}
	this->flags |= b_map[*++(*s)];
	*(*s)++;
}

static void	reset(void)
{
	this->flags = B_RESET;
	this->field_width = 0;
	this->precision = 0;
}

static bool	is_flag_set(uint16_t flag)
{
	return (this->flags & flag);
}

static void	print_flags(void)
{
	printf("flags | B_MINUS_FLAG : %d\n", this->is_flag_set(B_MINUS_FLAG));
	printf("flags | B_ZERO_FLAG : %d\n", this->is_flag_set(B_ZERO_FLAG));
	printf("flags | B_DOT_FLAG : %d\n", this->is_flag_set(B_DOT_FLAG));
	printf("flags | B_HASHTAG_FLAG : %d\n", this->is_flag_set(B_HASHTAG_FLAG));
	printf("flags | B_SPACE_FLAG : %d\n", this->is_flag_set(B_SPACE_FLAG));
	printf("flags | B_PLUS_FLAG : %d\n", this->is_flag_set(B_PLUS_FLAG));
	printf("flags | FORMAT_IDENTIFIER : %d\n", this->flags & B_FORMAT_SPECIFIER);
	printf("flags | FIELD_WIDTH : %d\n", this->field_width);
	printf("flags | PRECISION : %d\n", this->precision);
}

Flags	*flags_construct(void)
{
	this->init = &init;
	this->reset = &reset;
	this->is_flag_set = &is_flag_set;
	this->print_flags = &print_flags;
	return (this);
}
