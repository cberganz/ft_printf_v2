/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:20:08 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/09 01:51:43 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_pointer(t_func f, t_printer *p)
{
	unsigned long	arg;

	arg = va_arg(p->args, unsigned long);
	if (arg)
	{
		bufferize_string("0x", f, p);
		bufferize_integer(arg, g_base_16, f, p);
	}
	else
		bufferize_string("(nil)", f, p);
}

void	handle_string(t_func f, t_printer *p)
{
	char	*arg;

	arg = va_arg(p->args, char *);
	if (arg)
		bufferize_string(arg, f, p);
	else
		bufferize_string("(null)", f, p);
}

void	handle_unsigned(t_func f, t_printer *p)
{
	unsigned int	arg;

	arg = va_arg(p->args, unsigned int);
	bufferize_integer(arg, g_base_10, f, p);
}

void	handle_percent(t_func f, t_printer *p)
{
	f('%', p);
}

