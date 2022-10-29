/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/29 19:12:16 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
