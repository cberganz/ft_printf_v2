/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:08:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/27 05:56:19 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

Printer	*printer_singleton(void);
# define this printer_singleton()

int		ft_printf(const char *s, ...) __attribute__ ((format (printf, 1, 2)));
void	construct() __attribute__((constructor));
void	destruct() __attribute__((destructor));

int	ft_printf(const char *s, ...)
{
	va_list	args;

	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
			this->bufferize_arg(args, &s);
		else
			this->bufferize_char(*(s++));
	}
	va_end(args);
	return (this->len);
}

void	construct(void)
{
	this->flags = flags_construct();
	memset(this->buffer, 0, BUFFER_SIZE);
	this->offset = 0;
	this->len = 0;
	this->flush = &flush;
	this->pass_argument = &pass_argument;
	this->handle_percent = &handle_percent;
	this->handle_char = &handle_char;
	this->handle_string = &handle_string;
	this->handle_pointer = &handle_pointer;
	this->handle_decimal = &handle_decimal;
	this->handle_unsigned = &handle_unsigned;
	this->handle_hexadecimal_lower = &handle_hexadecimal_lower;
	this->handle_hexadecimal_upper = &handle_hexadecimal_upper;
	this->bufferize_char = &bufferize_char;
	this->bufferize_string = &bufferize_string;
	this->bufferize_arg = &bufferize_arg;
	this->bufferize_integer = &bufferize_integer;
}

void destruct()
{
	this->flush();
	//memset(this, 0, BUFFER_SIZE);
}
