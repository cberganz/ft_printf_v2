/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:27:36 by cberganz          #+#    #+#             */
/*   Updated: 2021/12/03 13:40:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%' && is_arg(s + 1))
			s += case_treatment(s + 1, args, &len);
		else if (*s == '%')
			s += case_c('%', &len);
		else
			s += case_text(s, &len);
	}
	va_end(args);
	return (len);
}
