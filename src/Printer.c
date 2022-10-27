/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/27 05:06:51 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

Printer	*printer_singleton(void)
{
	static Printer	obj;

	return (&obj);
}
# define this printer_singleton()

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

void	bufferize_arg(va_list args, const char **s)
{
	this->flags->init(s);
	g_handler[(this->flags->flags & B_FORMAT_SPECIFIER) >> 8](args);
	//this->flags->print_flags();
	this->flags->reset();
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

void	pass_argument(va_list args)
{
	errno = EINVAL;
	exit(errno);
}

void	handle_percent(va_list args)
{
	bufferize_char('%');
}

void	handle_char(va_list args)
{
	char	c;

	c = va_arg(args, int);
	bufferize_char(c);
}

void	handle_string(va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	bufferize_string(s ? s : "(null)");
}

void	handle_pointer(va_list args)
{
	unsigned long	n;

	n = va_arg(args, unsigned long);
	bufferize_string("0x");
	bufferize_integer(n, 16, "0123456789abcdef");
}

void	handle_decimal(va_list args)
{
	int	n;

	n = va_arg(args, int);
	if (n < 0)
		this->bufferize_char('-');
	bufferize_integer(abs(n), 10, "0123456789");
}

void	handle_unsigned(va_list args)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	bufferize_integer(n, 10, "0123456789");
}

void	handle_hexadecimal_lower(va_list args)
{
	unsigned int	n;

	n = (unsigned int)va_arg(args, unsigned int);
	bufferize_integer(n, 16, "0123456789abcdef");
}

void	handle_hexadecimal_upper(va_list args)
{
	unsigned int	n;

	n = (unsigned int)va_arg(args, unsigned int);
	bufferize_integer(n, 16, "0123456789ABCDEF");
}
