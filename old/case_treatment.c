/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:54:17 by cberganz          #+#    #+#             */
/*   Updated: 2021/12/03 13:40:47 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	case_treatment(const char *s, va_list args, int *len)
{
	if (*s == 'c')
		case_c(va_arg(args, int), len);
	else if (*s == 's')
		case_s(va_arg(args, char *), len);
	else if (*s == 'p')
	{
		case_s("0x", len);
		case_p(va_arg(args, unsigned long), len);
	}
	else if (*s == 'd' || *s == 'i')
		case_i_d(va_arg(args, int), len);
	else if (*s == 'u')
		case_u(va_arg(args, unsigned int), len);
	else if (*s == 'x')
		case_x(va_arg(args, int), len);
	else if (*s == 'X')
		case_upperx(va_arg(args, int), len);
	else if (*s == '%')
		case_c('%', len);
	return (2);
}
