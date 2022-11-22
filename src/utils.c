/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:17 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/22 00:56:58 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

void	print_pre_width(long long offset, t_printer *p)
{
	int	c;

	c = 32 + ((p->f & F_ZERO) << 3);
	//c = 32 + 16 * ((p->f & (F_ZERO | F_DOT)) == 6) * (p->p <= p->_s_c - p->_s_s);
	if (p->f & F_DOT && offset - p->w + p->p + (p->sign != 0) <= 0)
		c = 32;
	else if (p->f & F_DOT && p->f & F_ZERO && offset + (p->_s_c - p->_s_s) > p->p && p->p >= p->_s_c - p->_s_s)
	{
		c = 32;
		offset = offset - p->p + (p->_s_c - p->_s_s);
		p->p += offset;
	}
	if (p->sign && c == '0')
		bufferize_char(p->sign, p, false);
	while (p->w && !(p->f & F_MINUS) && offset-- > 0)
		bufferize_char(c, p, true);
	if (p->sign && c != '0')
		bufferize_char(p->sign, p, false);
}

void	print_post_width(long long offset, t_printer *p)
{
	int	c;

	if (!p->w || !(p->f & F_MINUS))
		return ;
	c = 16 * ((p->f & (F_ZERO | F_DOT)) == 6) * (p->p <= p->_s_c - p->_s_s);
	while (offset-- > 0)
		bufferize_char(' ' + c, p, true);
}

void	print_prec(long long offset, t_printer *p)
{
	offset += p->sign != 0;
	p->w -= (offset > 0) * (offset * (p->w > offset) + p->w * (p->w <= offset));
	while (offset-- > 0)
		bufferize_char('0', p, true);
}

void	bufferize_string(char *s, t_func f, t_printer *p)
{
	while (*s)
		f(*s++, p, false);
}

t_printer	*restore(void)
{
	static t_printer	p;

	if (!p._n_s)
	{
		p._n_s = &*p.buffer;
		p._s_s = &*p.special_buffer;
		p._n_c = p._n_s;
		p._s_c = p._s_s;
		p._n_e = &p.buffer[BUFFER_SIZE - 1];
		p._s_e = &p.special_buffer[SPECIAL_BUFFER_SIZE - 1];
	}
	p.len = 0;
	return (&p);
}

void	read_integer(const char **s, uint32_t *ptr, bool offset)
{
	if (offset)
		(void)*(*s)++;
	while (isdigit(**s))
		*ptr = *ptr * 10 + *(*s)++ - '0';
	(void)*(*s)--;
}

int	ft_abs(int v)
{
	if (v > 0)
		return (v);
	else
		return (-v);
}
