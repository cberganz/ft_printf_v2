/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:17 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/27 13:47:00 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

void	print_pre_width(long long offset, t_printer *p)
{
	int	c;

	offset += - (p->sign[0] != 0) - (p->sign[1] != 0);
	c = 32 + ((p->f & F_ZERO) << 3);
	if (p->f & F_DOT)
	{
		if (p->p <= (p->_s_c - p->_s_s))
			c = 32;
		if (p->p > offset + (p->_s_c - p->_s_s) && **p->format != 's')
			offset = 0;
		else if (**p->format != 's' && offset + (p->_s_c - p->_s_s) >= p->p
			&& p->p >= p->_s_c - p->_s_s)
		{
			c = 32;
			offset = offset - p->p + (p->_s_c - p->_s_s);
			if (!(p->f & F_MINUS))
				p->p += offset;
		}
	}
	if (*p->sign && c == '0')
		bufferize_string(p->sign, &bufferize_char, p);
	while (p->w && !(p->f & F_MINUS) && offset-- > 0)
		bufferize_char(c, p, true);
	if (*p->sign && c != '0')
		bufferize_string(p->sign, &bufferize_char, p);
}

void	print_post_width(long long offset, t_printer *p)
{
	offset += - (p->sign[0] != 0) - (p->sign[1] != 0);
	if (!p->w || !(p->f & F_MINUS))
		return ;
	while (offset-- > 0)
		bufferize_char(' ', p, true);
}

void	print_prec(long long offset, t_printer *p)
{
	offset += (p->sign[0] != 0) + (p->sign[1] != 0);
	p->w -= (offset > 0) * (offset * (p->w > offset) + p->w * (p->w <= offset));
	while (offset-- > 0)
		bufferize_char('0', p, true);
}

void	bufferize_string(char *s, t_func f, t_printer *p)
{
	while (*s)
		f(*s++, p, false);
}

void	read_integer(const char **s, uint32_t *ptr, bool offset)
{
	if (offset)
		(void)*(*s)++;
	while (isdigit(**s))
		*ptr = *ptr * 10 + *(*s)++ - '0';
	(void)*(*s)--;
}
