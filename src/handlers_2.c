/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:20:08 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/08 11:25:49 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_pointer(t_func f, t_printer *printer)
{
	unsigned long	arg;

	arg = va_arg(printer->args, unsigned long);
	if (arg)
	{
		bufferize_string("0x", f, printer);
		bufferize_integer(arg, 16, "0123456789abcdef", f, printer);
	}
	else
		bufferize_string("(nil)", f, printer);
}

void	handle_string(t_func f, t_printer *printer)
{
	char	*arg;

	arg = va_arg(printer->args, char *);
	if (arg)
		bufferize_string(arg, f, printer);
	else
		bufferize_string("(null)", f, printer);
}

void	handle_unsigned(t_func f, t_printer *printer)
{
	unsigned int	arg;

	arg = va_arg(printer->args, unsigned int);
	bufferize_integer(arg, 10, "0123456789", f, printer);
}

void	handle_illegal_argument(t_func f, t_printer *printer)
{
	errno = EINVAL;
	exit(errno);
}
