/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/09 02:22:31 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include <ctype.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>

# define BUFFER_SIZE 1048

typedef struct s_printer
{
	const char		**format;
	va_list			args;
	uint8_t			flags;
	uint32_t		width;
	uint32_t		prec;
	uint8_t			sign;
	char			buffer[BUFFER_SIZE];
	char			*_n_start;
	char			*_n_current;
	char			*_n_end;
	char			*_n_save_current;
	char			special_buffer[4096];
	char			*_s_start;
	char			*_s_current;
	char			*_s_end;
	size_t			len;
}	t_printer;

typedef void		(*t_func)(char, t_printer *);
typedef void		(*t_handler)();
char				*init_flags(const char **s, t_printer *printer);
void				reset_flags(t_printer *printer);
int					ft_abs(int v);

typedef struct s_base {
	int				size;
	char			*string;
}	t_base;

extern const t_base	g_base_10;
extern const t_base	g_base_16;
extern const t_base	g_base_16_upper;

#endif
