/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:56 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/31 19:56:23 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

void	handle_unsigned(t_func f)
{
	this->uint = va_arg(this->args, unsigned int);
	bufferize_integer(this->uint, 10, "0123456789", f);
}
