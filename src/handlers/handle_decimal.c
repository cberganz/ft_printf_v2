/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:28 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/02 20:12:27 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

void	handle_decimal(t_func f)
{
	this->i = va_arg(this->args, int);
	if (this->i < 0)
	{
		bufferize_char('-');
		if (!this->flags.prec)
			this->flags.sign = 1;
	}
	else if (this->flags.flags & B_PLUS_FLAG)
	{
		bufferize_char('+');
		if (!this->flags.prec)
			this->flags.sign = 1;
	}
	else if (this->flags.flags & B_SPACE_FLAG)
	{
		bufferize_char(' ');
		if (!this->flags.prec)
			this->flags.sign = 1;
	}
	bufferize_integer((unsigned int)abs(this->i), 10, "0123456789", f);
}
