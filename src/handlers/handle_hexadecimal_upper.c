/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hexadecimal_upper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:38 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/29 22:27:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_hexadecimal_upper(void)
{
	this->uint = va_arg(this->args, unsigned int);
	if (this->flags.flags & B_HASHTAG_FLAG)
		bufferize_string("0X");
	bufferize_integer(this->uint, 16, "0123456789ABCDEF");
}
