/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:17 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/09 02:21:53 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_width(long long offset, t_printer *p)
{
	while (offset-- > 0)
		bufferize_char(32 + ((p->flags & B_ZERO_FLAG) << 3), p);
}

void	bufferize_string(char *s, t_func f, t_printer *p)
{
	while (*s)
		f(*s++, p);
}

void	bufferize_integer(unsigned long n, t_base base, t_func f, \
							t_printer *p)
{
	if (n >= (unsigned long)base.size)
	{
		bufferize_integer(n / base.size, base, f, p);
		f(base.string[n % base.size], p);
	}
	else
		f(base.string[n], p);
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
	return (&p);
}

int	ft_abs(int v)
{
	if (v > 0)
		return (v);
	else
		return (-v);
}
