/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/30 20:58:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

void	handle_pointer(void)
{
	this->ulong = va_arg(this->args, unsigned long);
	if (this->ulong)
	{
		bufferize_string("0x");
		bufferize_integer(this->ulong, 16, "0123456789abcdef");
	}
	else
		bufferize_string("(nil)");
}
