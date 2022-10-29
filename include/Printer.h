/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/30 00:07:29 by cberganz         ###   ########.fr       */
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
# define this printer_singleton()

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
	void			(*bufferize_integer)(unsigned long, int, char*);

}	Printer;

typedef void	(*t_handler)();

#endif
