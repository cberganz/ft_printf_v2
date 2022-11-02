/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:20:21 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/02 19:19:50 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
# define this printer_singleton()

void	bufferize_string(char *s, t_func f)
{
	while (*s)
		f(*s++);
}
