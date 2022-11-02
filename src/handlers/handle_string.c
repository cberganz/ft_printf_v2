/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/02 21:34:54 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

void	handle_string(t_func f)
{
	this->s = va_arg(this->args, char *);
	if (this->s)
		bufferize_string(this->s, f);
	else
		bufferize_string("(null)", f);
}
