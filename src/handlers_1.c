/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:18:19 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/08 14:47:00 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_char(t_func f, t_printer	*printer)
{
	char	arg;

	arg = va_arg(printer->args, int);
	f(arg, printer);
}

void	handle_hexadecimal_lower(t_func f, t_printer *printer)
{
	unsigned int	arg;

	arg = va_arg(printer->args, unsigned int);
	if ((printer->flags.flags & B_HASHTAG_FLAG) && arg != 0)
		bufferize_string("0x", f, printer);
	bufferize_integer(arg, 16, "0123456789abcdef", f, printer);
}

void	handle_hexadecimal_upper(t_func f, t_printer *printer)
{
	unsigned int	arg;

	arg = va_arg(printer->args, unsigned int);
	if ((printer->flags.flags & B_HASHTAG_FLAG) && arg != 0)
		bufferize_string("0X", f, printer);
	bufferize_integer(arg, 16, "0123456789ABCDEF", f, printer);
}

void	handle_percent(t_func f, t_printer *printer)
{
	f('%', printer);
}

void	handle_decimal(t_func f, t_printer	*printer)
{
	int	arg;

	arg = va_arg(printer->args, int);
	if (!printer->flags.prec)
		printer->flags.sign = 1;
	if (arg < 0)
	{
		bufferize_char('-', printer);
//		if (!printer->flags.prec)
//			printer->flags.sign = 1;
	}
	else if (printer->flags.flags & B_PLUS_FLAG)
	{
		bufferize_char('+', printer);
	//	if (!printer->flags.prec)
	//		printer->flags.sign = 1;
	}
	else if (printer->flags.flags & B_SPACE_FLAG)
	{
		bufferize_char(' ', printer);
	//	if (!printer->flags.prec)
	//		printer->flags.sign = 1;
	}
	else
		printer->flags.sign = 0;
	bufferize_integer((unsigned int)abs(arg), 10, "0123456789", f, printer);
}
