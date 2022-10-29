/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:28 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/29 22:46:45 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_decimal(void)
{
	this->i = va_arg(this->args, int);
	if (this->i < 0)
		this->bufferize_char('-');
	else if (this->flags.flags & B_PLUS_FLAG)
		this->bufferize_char('+');
	else if (this->flags.flags & B_SPACE_FLAG)
		this->bufferize_char(' ');
	bufferize_integer((unsigned int)abs(this->i), 10, "0123456789");
}
