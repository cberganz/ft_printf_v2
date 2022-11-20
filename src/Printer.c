/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/20 19:29:09 by cberganz         ###   ########.fr       */
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
	write(1, p->buffer, p->_n_current - p->_n_start);
	p->len += p->_n_current - p->_n_start;
	p->_n_current = p->_n_start;
}

void	bufferize_arg(t_printer *p)
{
	p->_n_save_current = init_flags(p->format, p);
	p->s_prec = p->prec;
	p->_s_current = p->_s_start;
	g_handler[g_jump[(int)*(*p->format)++]](&special_bufferize_char, p);
	*p->_s_current = '\0';
	if (p->width && !(p->flags & B_MINUS_FLAG))
		print_width(p->width - (p->_s_current - p->_s_start) - (p->sign != 0), p);
	if (p->sign)
		bufferize_char(p->sign, p, false);
	if (p->prec && g_jump[(int)*(*p->format - 1)] >= 5)
		print_prec(p->prec - (p->_s_current - p->_s_start), p);
	bufferize_string(p->_s_start, &bufferize_char, p);
	if (p->width && p->flags & B_MINUS_FLAG)
		print_width(p->width - (p->_s_current - p->_s_start) - (p->sign != 0), p);
	if (*(*p->format - 1) == 'c' && *(p->_s_current - 1) == '\0')
		bufferize_char('\0', p, false);
	reset_flags(p);
}

void	bufferize_increment(t_printer *p)
{
	*p->_n_current++ = **p->format;
	if (*(*p->format)++ == '\n' || p->_n_current == p->_n_end)
		flush(p);
}

void	special_bufferize_char(char c, t_printer *p)
{
	if (p->_s_current != p->_s_end && (!(p->flags & B_DOT_FLAG) || g_jump[(int)*(*p->format - 1)] >= 5 || p->s_prec > 0))
	{
		*p->_s_current++ = c;
		if (g_jump[(int)*(*p->format - 1)] < 5 && p->flags & B_DOT_FLAG)
			p->s_prec--;
	}
}

void	bufferize_char(char c, t_printer *p, bool width)
{
	if (!(p->flags & B_DOT_FLAG) || p->prec > 0 || g_jump[(int)*(*p->format - 1)] >= 5 || width)
	{
		*p->_n_current++ = c;
		if (c == '\n' || p->_n_current == p->_n_end)
			flush(p);
		if (g_jump[(int)*(*p->format - 1)] < 5 && p->flags & B_DOT_FLAG && !width)
			p->prec--;
	}
}
