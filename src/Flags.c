/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/21 20:48:36 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

static const uint8_t	g_flags_map[128] = {
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	16,	0,	0,	8,	0,	64,	0,	0,
	0,	0,	0,	32,	0,	1,	4,	0,	2,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	64,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	64,
	64,	0,	0,	0,	0,	64,	0,	0,	0,	0,
	0,	0,	64,	0,	0,	64,	0,	64,	0,	0,
	64,	0,	0,	0,	0,	0,	0,	0
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
	p->sign = 0;
	p->w = 0;
	p->p = 0;
	p->_n_save_c = NULL;
}
