/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:17 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/08 14:15:47 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_width(long long offset, t_printer *printer)
{
	char	c;

	if (offset <= 0)
		return ;
	if (printer->flags.flags & B_ZERO_FLAG)
		c = '0';
	else
		c = ' ';
	while (offset-- > 0)
		bufferize_char(c, printer);
}

void	bufferize_string(char *s, t_func f, t_printer *printer)
{
	while (*s)
		f(*s++, printer);
}

void	bufferize_integer(unsigned long n, int base, char *base_str, t_func f, t_printer *printer)
{
	//printf("test: %ld\n", n);
	if (n >= base)
	{
		bufferize_integer(n / base, base, base_str, f, printer);
		f(base_str[n % base], printer);
	}
	else
		f(base_str[n], printer);
}
