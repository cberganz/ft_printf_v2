/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:08:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:11:31 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printer	*printer(void)
{
	static t_printer	obj;

	return (&obj);
}

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
	va_start(printer()->args, s);
	printer()->format = &s;
	while (*s)
		g_format_string_handler[*s == '%'](printer());
	va_end(printer()->args);
	flush(printer());
	return (printer()->len);
}

void	constructor(void)
{
	printer()->flags.sign = 0;
	printer()->_start = &printer()->buffer[0];
	printer()->_current = printer()->_start;
	printer()->_end = &printer()->buffer[BUFFER_SIZE - 1];
	printer()->_save_current = NULL;
	printer()->len = 0;
}
