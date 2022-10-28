/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:35:45 by cberganz          #+#    #+#             */
/*   Updated: 2021/12/02 15:35:47 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_x(unsigned int nbr, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr >= 16)
	{
		case_x(nbr / 16, len);
		case_c(base[nbr % 16], len);
	}
	else
		case_c(base[nbr], len);
}
