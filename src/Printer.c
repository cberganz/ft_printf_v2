/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/28 16:33:03 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

# define this printer_singleton()

Printer	*printer_singleton(void)
{
	static Printer	obj;

	return (&obj);
}

static const t_handler	g_handler[10] = {
	&pass_argument,
	&handle_percent,
	&handle_char,
	&handle_string,
	&handle_pointer,
	&handle_decimal,
	&handle_decimal,
	&handle_unsigned,
	&handle_hexadecimal_lower,
	&handle_hexadecimal_upper,
};

void	flush(void)
{
	write(1, this->buffer, this->offset);
	this->offset = 0;
}

void	bufferize_arg()
{
	this->flags->init(this->format);
	g_handler[(this->flags->flags & B_FORMAT_SPECIFIER) >> 8](this->args);
	this->flags->reset();
}

void	bufferize_increment()
{
	this->buffer[this->offset++] = **this->format;
	//this->buffer[this->offset] = '\0';
	if (*(*this->format)++ == '\n' || this->offset == BUFFER_SIZE)
		this->flush();
	this->len++;
}

void	bufferize_char(char c)
{
	this->buffer[this->offset++] = c;
	if (c == '\n' || this->offset == BUFFER_SIZE)
		this->flush();
	this->len++;
}

void	bufferize_string(char *s)
{
	while (*s)
		this->bufferize_char(*s++);
}

void	bufferize_integer(unsigned long n, int base, char *base_str)
{
	if (n >= base)
	{
		this->bufferize_integer(n / base, base, base_str);
		this->bufferize_char(base_str[n % base]);
	}
	else
		this->bufferize_char(base_str[n]);
}

void	pass_argument()
{
	errno = EINVAL;
	exit(errno);
}

void	handle_percent()
{
	bufferize_char('%');
}

void	handle_char()
{
	this->c = va_arg(this->args, int);
	bufferize_char(this->c);
}

void	handle_string()
{
	this->s = va_arg(this->args, char *);
	bufferize_string(this->s ? this->s : "(null)");
}

void	handle_pointer()
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

void	handle_decimal()
{
	this->i = va_arg(this->args, int);
	if (this->i < 0)
		this->bufferize_char('-');
	bufferize_integer((unsigned int)abs(this->i), 10, "0123456789");
}

void	handle_unsigned()
{
	this->uint = va_arg(this->args, unsigned int);
	bufferize_integer(this->uint, 10, "0123456789");
}

void	handle_hexadecimal_lower()
{
	this->uint = va_arg(this->args, unsigned int);
	bufferize_integer(this->uint, 16, "0123456789abcdef");
}

void	handle_hexadecimal_upper()
{
	this->uint = va_arg(this->args, unsigned int);
	bufferize_integer(this->uint, 16, "0123456789ABCDEF");
}
