/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:08:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/25 23:08:39 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.h"

const t_base				g_base_10 = {10, "0123456789"};
const t_base				g_base_16 = {16, "0123456789abcdef"};
const t_base				g_base_16_upper = {16, "0123456789ABCDEF"};

static const t_func_handler	g_format_string_handler[3] = {
	&bufferize_increment,
	&bufferize_arg
};

int		ft_printf(const char *s, ...) __attribute__ ((format (printf, 1, 2)));
void	destructor(void) __attribute__ ((destructor));

int	ft_printf(const char *s, ...)
{
	t_printer	*p;

	p = restore();
	va_start(p->args, s);
	p->format = &s;
	while (*s)
		g_format_string_handler[*s == '%'](p);
	va_end(p->args);
	flush(p);
	return (p->len);
}

void	destructor(void)
{
	free(restore()->special_buffer);
}
