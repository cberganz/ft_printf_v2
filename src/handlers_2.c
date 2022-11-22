/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:20:08 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/22 12:25:05 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

static const char	g_char_table[49] = {
	0,		'-',	0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		' ',	'-',	0,		0,
	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
	0,		0,		'+',	'-',	0,		0,		0,		0,		0,		0,
	0,		0,		0,		0,		0,		0,		0,		'+',	'-'
};

void	handle_decimal(t_func f, t_printer	*p)
{
	int	arg;

	arg = va_arg(p->args, int);
	p->sign = arg < 0;
	p->sign |= p->f & (F_PLUS | F_SPACE);
	if (p->sign)
		p->sign = g_char_table[p->sign];
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
		bufferize_integer((unsigned int)abs(arg), g_base_10, f, p);
}

void	handle_pointer(t_func f, t_printer *p)
{
	unsigned long	arg;

	arg = va_arg(p->args, unsigned long);
	if (arg)
	{
		bufferize_string("0x", f, p);
		bufferize_integer(arg, g_base_16, f, p);
	}
	else
		bufferize_string("(nil)", f, p);
}

void	handle_unsigned(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
		bufferize_integer(arg, g_base_10, f, p);
}

void	bufferize_integer(unsigned long n, t_base base, t_func f, \
							t_printer *p)
{
	if (n >= (unsigned long)base.size)
	{
		bufferize_integer(n / base.size, base, f, p);
		f(base.string[n % base.size], p, false);
	}
	else
		f(base.string[n], p, false);
}

void	handle_percent(t_func f, t_printer *p)
{
	f('%', p, false);
}
