/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/03 22:08:25 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include "Flags.h"
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>

# define BUFFER_SIZE 1048

typedef void	(*t_func)();

typedef struct s_printer
{
	const char		**format;
	va_list			args;
	t_flags			flags;
	char			buffer[BUFFER_SIZE];
	char			*_start;
	char			*_current;
	char			*_end;
	char			*_save_current;
	char			*special_buffer;
	char			*_special_start;
	char			*_special_current;
	char			*_special_end;
	size_t			len;
}	t_printer;

typedef void	(*t_handler)();
char			*init_flags(const char **s, t_printer *printer);
void			reset_flags(t_printer *printer);

#endif
