/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:44:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:01:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	flush(t_printer *printer)
{
	write(1, printer->buffer, printer->_current - printer->_start);
	printer->len += printer->_current - printer->_start;
	printer->_current = printer->_start;
}

#define OPT_SIZE 4096

void	print_width(size_t offset, t_printer *printer)
{
	char	c;

	if (printer->flags.flags & B_ZERO_FLAG)
		c = '0';
	else
		c = ' ';
	while (offset-- > 0)
		bufferize_char(c, printer);
}

void	width_handler(t_printer *printer)
{
	if (printer->flags.flags & B_MINUS_FLAG)
	{
		g_handler[g_jump_table[*(*printer->format)++]](&bufferize_char, printer);
		if (printer->flags.width - (printer->_current - printer->_save_current) > 0)
			print_width(printer->flags.width - (printer->_current - printer->_save_current), printer);
	}
	else
	{
		printer->special_buffer = (char *)malloc(OPT_SIZE);
		if (!printer->special_buffer)
			exit(1);
		memset(printer->special_buffer, 0, OPT_SIZE * sizeof(char));
		printer->_special_current = printer->special_buffer;
		g_handler[g_jump_table[*(*printer->format)++]](&special_bufferize_char, printer);
		*printer->_special_current = '\0';
		if (printer->flags.width - (printer->_special_current - printer->special_buffer) - printer->flags.sign > 0)
			print_width(printer->flags.width - (printer->_special_current - printer->special_buffer) - printer->flags.sign, printer);
		bufferize_string(printer->special_buffer, &bufferize_char, printer);
		free(printer->special_buffer);
	}
}

void	bufferize_arg(t_printer *printer)
{
	printer->_save_current = init_flags(printer->format, printer);
	if (**printer->format == 'd' || **printer->format == 'i' || **printer->format == 'u' || **printer->format == 'x' || **printer->format == 'X')
	{
		if (printer->flags.width == 0)
		{
			printer->flags.width = printer->flags.prec;
			printer->flags.flags |= B_ZERO_FLAG;
			printer->flags.flags &= 0b11111011;
		}
	}
	if (printer->flags.width)
		width_handler(printer);
	else
		g_handler[g_jump_table[*(*printer->format)++]](&bufferize_char, printer);
	reset_flags(printer);
}

void	bufferize_increment(t_printer *printer)
{
	*printer->_current++ = **printer->format;
	if (*(*printer->format)++ == '\n' || printer->_current == printer->_end)
		flush(printer);
}

void	special_bufferize_char(char c, t_printer *printer)
{
	if (!(printer->flags.flags & B_DOT_FLAG) || printer->flags.prec > 0)
	{
		*printer->_special_current++ = c;
		if (c == '\n' || printer->_current == printer->_end)
			flush(printer);
		if (printer->flags.flags & B_DOT_FLAG)
			printer->flags.prec--;
	}
}

void	bufferize_char(char c, t_printer *printer)
{
	if (!(printer->flags.flags & B_DOT_FLAG) || printer->flags.prec > 0)
	{
		*printer->_current++ = c;
		if (c == '\n' || printer->_current == printer->_end)
			flush(printer);
		if (printer->flags.flags & B_DOT_FLAG)
			printer->flags.prec--;
	}
}

void	bufferize_integer(unsigned long n, int base, char *base_str, t_func f, t_printer *printer)
{
	if (n >= base)
	{
		bufferize_integer(n / base, base, base_str, f, printer);
		f(base_str[n % base], printer);
	}
	else
		f(base_str[n], printer);
}
