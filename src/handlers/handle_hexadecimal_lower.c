/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hexadecimal_lower.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:34 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:00:19 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_hexadecimal_lower(t_func f, t_printer *printer)
{
	unsigned int	arg;

	arg = va_arg(printer->args, unsigned int);
	if ((printer->flags.flags & B_HASHTAG_FLAG) && arg != 0)
		bufferize_string("0x", f, printer);
	bufferize_integer(arg, 16, "0123456789abcdef", f, printer);
}
