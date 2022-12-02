/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/28 00:16:45 by charles          ###   ########.fr       */
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
{&handle_illegal_argument, F_FLAG_SPECIFIER},
{&handle_percent, F_FLAG_SPECIFIER},
{&handle_char, F_ZERO | F_HASHTAG | F_SPACE | F_PLUS | F_DOT},
{&handle_string, F_ZERO | F_HASHTAG | F_SPACE | F_PLUS},
{&handle_pointer, F_ZERO | F_HASHTAG | F_SPACE | F_PLUS | F_DOT},
{&handle_decimal, F_HASHTAG},
{&handle_decimal, F_HASHTAG},
{&handle_unsigned, F_HASHTAG | F_SPACE | F_PLUS},
{&handle_hexadecimal_lower, F_SPACE | F_PLUS},
{&handle_hexadecimal_upper, F_SPACE | F_PLUS},
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
	p->f &= ~g_handler[g_jump[(int)**p->format]].ignore;
	p->save_p = p->p;
	g_handler[g_jump[(int)**p->format]].f(&special_bufferize_char, p);
	print_pre_width(p->w - (p->_s_c - p->_s_s), p);
	if (g_jump[(int)**p->format] >= 4)
		print_prec(p->p - (p->_s_c - p->_s_s) - (p->_n_c - p->_n_save_c), p);
	bufferize_string(p->_s_s, &bufferize_char, p);
	if (**p->format == 'c' && *(p->_s_c - 1) == '\0')
		bufferize_char('\0', p, false);
	print_post_width(p->w - (p->_s_c - p->_s_s), p);
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
	if (p->_s_c == p->_s_e)
		realloc_special_buffer(p);
	if ((!(p->f & F_DOT) || g_jump[(int)**p->format] >= 5 || p->save_p > 0))
	{
		*p->_s_c++ = c;
		*p->_s_c = '\0';
		if (g_jump[(int)**p->format] < 5 && p->f & F_DOT)
			p->save_p--;
	}
}

void	bufferize_char(char c, t_printer *p, bool width)
{
	if (!(p->f & F_DOT) || p->p > 0 || g_jump[(int)**p->format] >= 4 || width)
	{
		*p->_n_c++ = c;
		if (c == '\n' || p->_n_c == p->_n_e)
			flush(p);
		if (g_jump[(int)**p->format] < 5 && p->f & F_DOT && !width)
			p->p--;
	}
}
