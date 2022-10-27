/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/27 05:08:49 by charles          ###   ########.fr       */
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
	Flags		*flags;
	char		buffer[BUFFER_SIZE];
	uint16_t	offset;
	size_t		len;

	void		(*flush)();

	void		(*pass_argument)(va_list);
	void		(*handle_percent)(va_list);
	void		(*handle_char)(va_list);
	void		(*handle_string)(va_list);
	void		(*handle_pointer)(va_list);
	void		(*handle_decimal)(va_list);
	void		(*handle_unsigned)(va_list);
	void		(*handle_hexadecimal_lower)(va_list);
	void		(*handle_hexadecimal_upper)(va_list);

	void		(*bufferize_arg)(va_list, const char**);
	void		(*bufferize_char)(char);
	void		(*bufferize_string)(char*);
	void		(*bufferize_integer)(unsigned long, int, char*);

}	Printer;

typedef void	(*t_handler)(va_list);

#endif
