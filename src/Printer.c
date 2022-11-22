/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/22 13:02:30 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

static const uint8_t	g_jump[128] = {
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	9,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,
	5,	0,	0,	0,	0,	6,	0,	0,	0,	0,
	0,	0,	4,	0,	0,	3,	0,	7,	0,	0,
	8,	0,	0,	0,	0,	0,	0,	0
};

static const t_handler	g_handler[10] = {
	&handle_illegal_argument,
	&handle_percent,
	&handle_char,
	&handle_string,
	&handle_pointer,
	&handle_decimal,
	&handle_decimal,
	&handle_unsigned,
	&handle_hexadecimal_lower,
	&handle_hexadecimal_upper,
};

void	flush(t_printer *p)
{
	write(1, p->buffer, p->_n_c - p->_n_s);
	p->len += p->_n_c - p->_n_s;
	p->_n_c = p->_n_s;
}

void	bufferize_arg(t_printer *p)
{
	p->_n_save_c = init_flags(p->format, p);
	p->save_p = p->p;
	g_handler[g_jump[(int)**p->format]](&special_bufferize_char, p);
	print_pre_width(p->w - (p->_s_c - p->_s_s) - (p->sign != 0), p);
	if (g_jump[(int)**p->format] >= 5)
		print_prec(p->p - (p->_s_c - p->_s_s) - (p->_n_c - p->_n_save_c), p);
	bufferize_string(p->_s_s, &bufferize_char, p);
	if (**p->format == 'c' && *(p->_s_c - 1) == '\0')
		bufferize_char('\0', p, false);
	print_post_width(p->w - (p->_s_c - p->_s_s) - (p->sign != 0), p);
	reset_flags(p);
}

void	bufferize_increment(t_printer *p)
{
	*p->_n_c++ = **p->format;
	if (*(*p->format)++ == '\n' || p->_n_c == p->_n_e)
		flush(p);
}

void	special_bufferize_char(char c, t_printer *p)
{
	if (p->_s_c != p->_s_e && (!(p->f & F_DOT)
			|| g_jump[(int)**p->format] >= 5 || p->save_p > 0))
	{
		*p->_s_c++ = c;
		*p->_s_c = '\0';
		if (g_jump[(int)**p->format] < 5 && p->f & F_DOT)
			p->save_p--;
	}
}

void	bufferize_char(char c, t_printer *p, bool width)
{
	if (!(p->f & F_DOT) || p->p > 0 || g_jump[(int)**p->format] >= 5 || width)
	{
		*p->_n_c++ = c;
		if (c == '\n' || p->_n_c == p->_n_e)
			flush(p);
		if (g_jump[(int)**p->format] < 5 && p->f & F_DOT && !width)
			p->p--;
	}
}
