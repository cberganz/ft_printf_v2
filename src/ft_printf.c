/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:08:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/29 05:03:59 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

Printer	*printer_singleton(void);
# define this printer_singleton()

int	ft_printf(const char *s, ...) __attribute__ ((format (printf, 1, 2)));
static void constructor() __attribute__((constructor));

static const t_handler	g_format_string_handler[3] =
{
	&bufferize_increment,
	&bufferize_arg
};

int	ft_printf(const char *s, ...)
{
	va_start(this->args, s);
	this->format = &s;
	while (*s)
		g_format_string_handler[*s == '%']();
	va_end(this->args);
	this->flush();
	return (this->len);
}

static void constructor(void)
{
	this->flags = flags_construct();
	this->_start = &this->buffer[0];
	this->_current = this->_start;
	this->_end = &this->buffer[BUFFER_SIZE - 1];
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
	this->bufferize_increment = &bufferize_increment;
	this->bufferize_string = &bufferize_string;
	this->bufferize_arg = &bufferize_arg;
	this->bufferize_integer = &bufferize_integer;
}
