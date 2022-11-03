/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:28 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:00:11 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_decimal(t_func f, t_printer	*printer)
{
	int	arg;

	arg = va_arg(printer->args, int);
	if (arg < 0)
	{
		bufferize_char('-', printer);
		if (!printer->flags.prec)
			printer->flags.sign = 1;
	}
	else if (printer->flags.flags & B_PLUS_FLAG)
	{
		bufferize_char('+', printer);
		if (!printer->flags.prec)
			printer->flags.sign = 1;
	}
	else if (printer->flags.flags & B_SPACE_FLAG)
	{
		bufferize_char(' ', printer);
		if (!printer->flags.prec)
			printer->flags.sign = 1;
	}
	bufferize_integer((unsigned int)abs(arg), 10, "0123456789", f, printer);
}
