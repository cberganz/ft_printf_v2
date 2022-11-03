/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_illegal_argument.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:21:03 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:00:41 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_illegal_argument(t_func f, t_printer *printer)
{
	errno = EINVAL;
	exit(errno);
}
