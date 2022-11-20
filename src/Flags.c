/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/20 16:27:37 by cberganz         ###   ########.fr       */
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
	if (g_flags_map[(int)*++(*s)] & B_FORMAT_SPECIFIER)
		return (p->_n_current);
	if (g_flags_map[(int)**s])
	{
		p->flags |= g_flags_map[(int)**s];
		if (g_flags_map[(int)**s] & B_DOT_FLAG)
		{
			(void)*(*s)++;
			while (isdigit(**s))
				p->prec = p->prec * 10 + *(*s)++ - '0';
			(void)*(*s)--;
		}
	}
	else if (isdigit(**s))
	{
		while (isdigit(**s))
			p->width = p->width * 10 + *(*s)++ - '0';
		(void)*(*s)--;
	}
	return (init_flags(s, p));
}

void	reset_flags(t_printer *p)
{
	p->flags = B_RESET;
	p->sign = 0;
	p->width = 0;
	p->prec = 0;
	p->_n_save_current = NULL;
}
