/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:56 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:01:18 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_unsigned(t_func f, t_printer *printer)
{
	unsigned int	arg;

	arg = va_arg(printer->args, unsigned int);
	bufferize_integer(arg, 10, "0123456789", f, printer);
}
