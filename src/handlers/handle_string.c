/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:01:11 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_string(t_func f, t_printer *printer)
{
	char	*arg;

	arg = va_arg(printer->args, char *);
	if (arg)
		bufferize_string(arg, f, printer);
	else
		bufferize_string("(null)", f, printer);
}
