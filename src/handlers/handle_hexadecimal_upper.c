/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hexadecimal_upper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:38 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/31 19:57:02 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

void	handle_hexadecimal_upper(t_func f)
{
	this->uint = va_arg(this->args, unsigned int);
	if ((this->flags.flags & B_HASHTAG_FLAG) && this->uint != 0)
		bufferize_string("0X", f);
	bufferize_integer(this->uint, 16, "0123456789ABCDEF", f);
}
