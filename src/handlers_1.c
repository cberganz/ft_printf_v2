/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:18:19 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/09 02:22:05 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const t_base		g_base_10 = {10, "0123456789"};
const t_base		g_base_16 = {16, "0123456789abcdef"};
const t_base		g_base_16_upper = {16, "0123456789ABCDEF"};

static const char	g_char_table[49] = {
	0,		'-',	0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		' ',	'-',	0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		'+',	'-',	0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		'+',	'-'
};

void	handle_char(t_func f, t_printer	*p)
{
	char	arg;

	arg = va_arg(p->args, int);
	f(arg, p);
}

void	handle_hexadecimal_lower(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if ((p->flags & B_HASHTAG_FLAG) && arg != 0)
		bufferize_string("0x", f, p);
	bufferize_integer(arg, g_base_16, f, p);
}

void	handle_hexadecimal_upper(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if ((p->flags & B_HASHTAG_FLAG) && arg != 0)
		bufferize_string("0X", f, p);
	bufferize_integer(arg, g_base_16_upper, f, p);
}

/*
**	'-' -> 45 -> 0b00101101
**	0b00110001 -> 49 : ^45 -> 0b00011100
**	0b00010001 -> 17 : ^45 -> 0b00111100
**	0b00100001 -> 33 : ^45 -> 0b00001100
**	0b00000001 -> 1  : ^45 -> 0b00000000
**	
**	'+' -> 43 -> 0b00101011
**	0b00110000 -> 48
**	0b00100000 -> 32
**	 >>5 -> 1 
**	
**	' ' -> 32 -> 0b00100000
**	0b00010000 -> 16
**	 >>5 -> 0
*/

void	handle_decimal(t_func f, t_printer	*p)
{
	int	arg;

	arg = va_arg(p->args, int);
	p->sign = arg < 0;
	p->sign |= (p->flags & (B_PLUS_FLAG | B_SPACE_FLAG));
	if (p->sign)
		bufferize_char(g_char_table[p->sign], p);
	p->sign = (p->sign && !p->prec);
	bufferize_integer((unsigned int)ft_abs(arg), g_base_10, f, p);
}

void	handle_illegal_argument(t_func f, t_printer *p)
{
	(void)f;
	(void)p;
}
