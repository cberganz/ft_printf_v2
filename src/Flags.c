/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:32:46 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:01:28 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*init_flags(const char **s, t_printer *printer)
{
	if (g_flags_map[*++(*s)] & B_FORMAT_SPECIFIER)
		return (printer->_current);
	if (g_flags_map[**s])
	{
		printer->flags.flags |= g_flags_map[**s];
		if (g_flags_map[**s] & B_DOT_FLAG)
		{
			*(*s)++;
			while (isdigit(**s))
				printer->flags.prec = printer->flags.prec * 10 + *(*s)++ - '0';
			*(*s)--;
		}
	}
	else if (isdigit(**s))
	{
		while (isdigit(**s))
			printer->flags.width = printer->flags.width * 10 + *(*s)++ - '0';
		*(*s)--;
	}
	init_flags(s, printer);
}

void	reset_flags(t_printer *printer)
{
	printer->flags.flags = B_RESET;
	printer->flags.sign = 0;
	printer->flags.width = 0;
	printer->flags.prec = 0;
	printer->_save_current = NULL;
}
