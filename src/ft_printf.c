/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:08:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/31 19:54:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

Printer	*printer_singleton(void);

int		ft_printf(const char *s, ...) \
	__attribute__ ((format (printf, 1, 2)));
void	constructor(void) \
	__attribute__((constructor));

static const t_handler	g_format_string_handler[3] = {
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

void	constructor(void)
{
	flags_construct();
	this->_start = &this->buffer[0];
	this->_current = this->_start;
	this->_end = &this->buffer[BUFFER_SIZE - 1];
	this->_save_current = NULL;
	this->len = 0;
	this->flush = &flush;
	this->bufferize_char = &bufferize_char;
	this->bufferize_increment = &bufferize_increment;
	this->bufferize_arg = &bufferize_arg;
	this->bufferize_integer = &bufferize_integer;
}
