/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:18:19 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/22 14:38:23 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

void	handle_char(t_func f, t_printer	*p)
{
	char	arg;

	arg = va_arg(p->args, int);
	f(arg, p, false);
}

void	handle_hexadecimal_lower(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
	{
		if ((p->f & F_HASHTAG) && arg != 0)
			strcpy(p->sign, "0x");
		bufferize_integer(arg, g_base_16, f, p);
	}
}

void	handle_hexadecimal_upper(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	if (!(!arg && (p->f & F_DOT) && p->p == 0))
	{
		if ((p->f & F_HASHTAG) && arg != 0)
			strcpy(p->sign, "0X");
		bufferize_integer(arg, g_base_16_upper, f, p);
	}
}

void	handle_string(t_func f, t_printer *p)
{
	char	*arg;

	arg = va_arg(p->args, char *);
	if (arg)
		bufferize_string(arg, f, p);
	else if (p->p >= 6 || !(p->f & F_DOT))
		bufferize_string("(null)", f, p);
}

void	handle_illegal_argument(t_func f, t_printer *p)
{
	(void)f;
	(void)p;
	errno = EINVAL;
	exit(1);
}
