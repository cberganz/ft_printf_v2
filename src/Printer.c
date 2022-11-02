/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/02 20:17:22 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

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

#define OPT_SIZE 4096

void	print_width(size_t offset)
{
	char	c;

	if (this->flags.flags & B_ZERO_FLAG)
		c = '0';
	else
		c = ' ';
	while (offset-- > 0)
		bufferize_char(c);
}

void	width_handler(void)
{
	if (this->flags.flags & B_MINUS_FLAG)
	{
		g_handler[g_jump_table[*(*this->format)++]](&bufferize_char);
		if (this->flags.width - (this->_current - this->_save_current) > 0)
			print_width(this->flags.width - (this->_current - this->_save_current));
	}
	else
	{
		this->special_buffer = (char *)malloc(OPT_SIZE);
		if (!this->special_buffer)
			exit(1);
		memset(this->special_buffer, 0, OPT_SIZE * sizeof(char));
		this->_special_current = this->special_buffer;
		g_handler[g_jump_table[*(*this->format)++]](&special_bufferize_char);
		*this->_special_current = '\0';
		if (this->flags.width - (this->_special_current - this->special_buffer) - this->flags.sign > 0)
			print_width(this->flags.width - (this->_special_current - this->special_buffer) - this->flags.sign);
		bufferize_string(this->special_buffer, &bufferize_char);
		free(this->special_buffer);
	}
}

void	bufferize_arg(void)
{
	this->_save_current = this->flags.init(this->format);
	if (**this->format == 'd' || **this->format == 'i' || **this->format == 'u' || **this->format == 'x' || **this->format == 'X')
	{
		if (this->flags.width == 0)
		{
			this->flags.width = this->flags.prec;
			this->flags.flags |= B_ZERO_FLAG;
			this->flags.flags &= 0b11111011;
		}
	}
	if (this->flags.width)
		width_handler();
	else
		g_handler[g_jump_table[*(*this->format)++]](&bufferize_char);
	this->flags.reset();
}

void	bufferize_increment(void)
{
	*this->_current++ = **this->format;
	if (*(*this->format)++ == '\n' || this->_current == this->_end)
		this->flush();
}

void	special_bufferize_char(char c)
{
	if (!(this->flags.flags & B_DOT_FLAG) || this->flags.prec > 0)
	{
		*this->_special_current++ = c;
		if (c == '\n' || this->_current == this->_end)
			this->flush();
		if (this->flags.flags & B_DOT_FLAG)
			this->flags.prec--;
	}
}

void	bufferize_char(char c)
{
	if (!(this->flags.flags & B_DOT_FLAG) || this->flags.prec > 0)
	{
		*this->_current++ = c;
		if (c == '\n' || this->_current == this->_end)
			this->flush();
		if (this->flags.flags & B_DOT_FLAG)
			this->flags.prec--;
	}
}

void	bufferize_integer(unsigned long n, int base, char *base_str, t_func f)
{
	if (n >= base)
	{
		bufferize_integer(n / base, base, base_str, f);
		f(base_str[n % base]);
	}
	else
		f(base_str[n]);
}
