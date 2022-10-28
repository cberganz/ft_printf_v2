/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_upperx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:35:11 by cberganz          #+#    #+#             */
/*   Updated: 2021/12/07 17:35:13 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_upperx(unsigned int nbr, int *len)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		case_upperx(nbr / 16, len);
		case_c(base[nbr % 16], len);
	}
	else
		case_c(base[nbr], len);
}
