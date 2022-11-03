/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:01:03 by cberganz         ###   ########.fr       */
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
