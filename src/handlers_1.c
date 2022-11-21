/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:18:19 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/21 15:39:43 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

void	handle_char(t_func f, t_printer	*p)
{
	char	arg;

	arg = va_arg(p->args, int);
	f(arg, p, false);
}

void	handle_hexadecimal_lower(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
	{
		if ((p->f & F_HASHTAG) && arg != 0)
			bufferize_string("0x", f, p);
		bufferize_integer(arg, g_base_16, f, p);
	}
}

void	handle_hexadecimal_upper(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
	{
		if ((p->f & F_HASHTAG) && arg != 0)
			bufferize_string("0X", f, p);
		bufferize_integer(arg, g_base_16_upper, f, p);
	}
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

void	handle_string(t_func f, t_printer *p)
{
	char	*arg;

	arg = va_arg(p->args, char *);
	if (arg)
		bufferize_string(arg, f, p);
	else if (p->p >= 6 || !(p->f & F_DOT))
		bufferize_string("(null)", f, p);
}

void	handle_illegal_argument(t_func f, t_printer *p)
{
	(void)f;
	(void)p;
}
