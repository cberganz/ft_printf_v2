/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/22 14:19:08 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

static const uint8_t	g_flags_map[128] = {
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	16,	64,	64,	8,	64,	64,	64,	64,
	64,	64,	64,	32,	64,	1,	4,	64,	2,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64,	64,	64,
	64,	64,	64,	64,	64,	64,	64,	64
};

char	*init_flags(const char **s, t_printer *p)
{
	if (g_flags_map[(int)*++(*s)] & F_FORMAT_SPECIFIER)
		return (p->_n_c);
	if (g_flags_map[(int)**s])
	{
		p->f |= g_flags_map[(int)**s];
		if (g_flags_map[(int)**s] & F_DOT)
			read_integer(s, &p->p, true);
	}
	else if (isdigit(**s))
		read_integer(s, &p->w, false);
	return (init_flags(s, p));
}

void	reset_flags(t_printer *p)
{
	p->f = F_RESET;
	p->sign[0] = 0;
	p->sign[1] = 0;
	p->w = 0;
	p->p = 0;
	p->_s_c = p->_s_s;
	*p->_s_c = '\0';
	p->_n_save_c = NULL;
	(void)*(*p->format)++;
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
