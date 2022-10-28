/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/28 16:36:24 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include "Flags.h"
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>

# define BUFFER_SIZE 1024

typedef struct s_printer
{
	const char		**format;
	va_list			args;
	Flags			*flags;
	char			buffer[BUFFER_SIZE];
	uint16_t		offset;
	size_t			len;
	char			c;
	char			*s;
	unsigned long	ulong;
	int				i;
	unsigned int	uint;

	void		(*flush)();

	void		(*pass_argument)();
	void		(*handle_percent)();
	void		(*handle_char)();
	void		(*handle_string)();
	void		(*handle_pointer)();
	void		(*handle_decimal)();
	void		(*handle_unsigned)();
	void		(*handle_hexadecimal_lower)();
	void		(*handle_hexadecimal_upper)();

	void		(*bufferize_arg)();
	void		(*bufferize_char)(char);
	void		(*bufferize_increment)();
	void		(*bufferize_string)(char*);
	void		(*bufferize_integer)(unsigned long, int, char*);

}	Printer;

typedef void	(*t_handler)();

#endif
