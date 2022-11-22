/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/22 00:52:46 by charles          ###   ########.fr       */
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
# include <stdbool.h>

/*
**	Brief: Object containing all necessary datas and pointers for the current
**		   call of ft_printf().
**
**	Attributes:
**		format:	double pointer to the current computed char of the format str.
**		args:	va_list containing the variadic arguments.
**		flags:	uint8_t containing all 6 possible flags of the project (-0+# .).
**				Each flag is represented by a byte defined below.
**		width:	contains the user defined minimum width or 0 if unspecified.
**		prec:	contains the user defined precision if the dot flag is present
**				or 0 if unspecified.
**		sign:	allows handling the difference between width and precision for
**				numeric types : width does not take into account the + or - or
**				blank character representing the sign.
**		buffer:	contains characters to be printed for the next flush.
**		_n_*:	pointers to locations in the buffer. _n_current points to the
**				next byte to be written.
**		len:	total len printed since since ft_printf call. Incremented by
**				the difference between _n_current and _n_s when the buffer
**				is flushed.
**		special_buffer:	a specific buffer for handling right alignment without
**				having to calculate an argument len before writing it. In this
**				specific case, the argument will be first written to this buffer
**				and its len will be known by pointer difference.
**		_s_*:	pointers to locations in the special buffer. _s_current points
**				to the next byte to be written. The difference between
**				_s_current and _s_start gives the len of the argument.
*/

# define BUFFER_SIZE				1024
# define SPECIAL_BUFFER_SIZE		4096

typedef struct s_printer
{
	const char		**format;
	va_list			args;
	uint8_t			f;
	uint32_t		w;
	uint32_t		p;
	uint32_t		save_p;
	uint8_t			sign;
	char			buffer[BUFFER_SIZE];
	char			*_n_s;
	char			*_n_c;
	char			*_n_e;
	char			*_n_save_c;
	size_t			len;
	char			special_buffer[SPECIAL_BUFFER_SIZE];
	char			*_s_s;
	char			*_s_c;
	char			*_s_e;
}	t_printer;

/*
**	brief:	binary flags mapping. Each flag is reprensented by a specific byte.
*/

# define F_RESET			0b00000000
# define F_MINUS			0b00000001
# define F_ZERO				0b00000010
# define F_DOT				0b00000100
# define F_HASHTAG			0b00001000
# define F_SPACE			0b00010000
# define F_PLUS				0b00100000
# define F_FLAG_SPECIFIER	0b00111111
# define F_FORMAT_SPECIFIER	0b11000000

/*
**	brief:	glabal constant containing data for base conversion.
**
**	t_base struct contains a base size and its associated characters.
*/

typedef struct s_base {
	int				size;
	char			*string;
}	t_base;

extern const t_base	g_base_10;
extern const t_base	g_base_16;
extern const t_base	g_base_16_upper;

typedef void		(*t_func)(char, t_printer *, bool);
typedef void		(*t_handler)();

char				*init_flags(const char **s, t_printer *printer);
void				reset_flags(t_printer *printer);
int					ft_abs(int v);
void				flush(t_printer *printer);
void				bufferize_char(char c, t_printer *printer, bool width);
void				special_bufferize_char(char c, t_printer *printer);
void				bufferize_increment(t_printer *printer);
void				bufferize_string(char *s, t_func f, t_printer *printer);
void				bufferize_integer(unsigned long n, t_base base, t_func f, \
					t_printer *printer);
void				bufferize_arg(t_printer *printer);
void				handle_illegal_argument(t_func f, t_printer *printer);
void				handle_percent(t_func f, t_printer *printer);
void				handle_char(t_func f, t_printer	*printer);
void				handle_string(t_func f, t_printer *printer);
void				handle_pointer(t_func f, t_printer *printer);
void				handle_decimal(t_func f, t_printer *printer);
void				handle_unsigned(t_func f, t_printer *printer);
void				handle_hexadecimal_lower(t_func f, t_printer *printer);
void				handle_hexadecimal_upper(t_func f, t_printer *printer);
void				print_prec(long long offset, t_printer *p);
void				flags_construct(void);
t_printer			*restore(void);
void				read_integer(const char **s, uint32_t *ptr, bool offset);
void	print_pre_width(long long offset, t_printer *p);
void	print_post_width(long long offset, t_printer *p);

#endif
