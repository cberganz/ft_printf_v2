/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_i_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:35:54 by cberganz          #+#    #+#             */
/*   Updated: 2021/12/02 15:35:56 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}

void	case_i_d(int n, int *len)
{
	unsigned int	nrecu;

	if (n < 0)
		case_c('-', len);
	nrecu = ft_abs(n);
	if (nrecu >= 10)
	{
		case_i_d(nrecu / 10, len);
		case_c(nrecu % 10 + '0', len);
	}
	else
		case_c(nrecu + '0', len);
}
