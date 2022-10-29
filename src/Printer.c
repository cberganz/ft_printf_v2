/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/30 00:11:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

Printer	*printer_singleton(void)
{
	static Printer	obj;

	return (&obj);
}

static const uint8_t	g_jump_table[128] = {
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	9,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,
	5,	0,	0,	0,	0,	6,	0,	0,	0,	0,
	0,	0,	4,	0,	0,	3,	0,	7,	0,	0,
	8,	0,	0,	0,	0,	0,	0,	0
};

static const t_handler	g_handler[10] = {
	&handle_illegal_argument,
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
	write(1, this->buffer, this->_current - this->_start);
	this->len += this->_current - this->_start;
	this->_current = this->_start;
}

void	bufferize_arg(void)
{
	this->_save_current = this->flags.init(this->format);
	g_handler[g_jump_table[*(*this->format)++]](this->args);
	this->flags.reset();
}

void	bufferize_increment(void)
{
	*this->_current++ = **this->format;
	if (*(*this->format)++ == '\n' || this->_current == this->_end)
		this->flush();
}

void	bufferize_char(char c)
{
	*this->_current++ = c;
	if (c == '\n' || this->_current == this->_end)
		this->flush();
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
