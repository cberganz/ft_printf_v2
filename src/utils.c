/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:17 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/21 01:39:47 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

void	print_width(long long offset, t_printer *p)
{
	int	c;

	c = 32 + ((p->flags & B_ZERO_FLAG) << 3);
	if (p->flags & B_DOT_FLAG && offset - p->width + p->prec + (p->sign != 0) <= 0)
		c = 32;
	while (offset-- > 0)
		bufferize_char(c, p, true);
}

void	print_prec(long long offset, t_printer *p)
{
	if (offset > 0 && p->width > offset)
		p->width -= offset;
	else if (offset > 0 && offset >= p->width)
		p->width = 0;
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

	if (!p._n_start)
	{
		p._n_start = &*p.buffer;
		p._n_current = p._n_start;
		p._n_end = &p.buffer[BUFFER_SIZE - 1];
		p._s_start = &*p.special_buffer;
		p._s_end = &p.special_buffer[BUFFER_SIZE - 1];
	}
	p.len = 0;
	return (&p);
}

int	ft_abs(int v)
{
	if (v > 0)
		return (v);
	else
		return (-v);
}
