/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:42:08 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 21:46:12 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>

typedef struct s_flags {
	uint8_t		flags;
	uint32_t	width;
	uint32_t	prec;
	uint8_t		sign;
}	t_flags;

#endif // PRINTER_H
