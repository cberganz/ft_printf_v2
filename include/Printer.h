/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/01 16:29:16 by cberganz         ###   ########.fr       */
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
	Flags			flags;
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
	char			c;
	char			*s;
	unsigned long	ulong;
	int				i;
	unsigned int	uint;

	void			(*flush)();

	void			(*bufferize_arg)();
	void			(*bufferize_char)(char);
	void			(*bufferize_increment)();
	void			(*bufferize_integer)(unsigned long, int, char*, t_func);

}	Printer;

typedef void	(*t_handler)();

#endif
