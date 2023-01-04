/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:06:30 by cberganz          #+#    #+#             */
/*   Updated: 2023/01/04 06:31:51 by cberganz         ###   ########.fr       */
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
**	@brief: The size of the buffer used to reduce i/o operations.
**
**	BUFFER_SIZE: Fixing it to the standard default buffer size allows to make
**				 the right compromise between optimizing i/o operations and
**				 minimizing the memory used to store the buffer.
**	SPECIAL_BUFFER_START_SIZE: The special buffer is dynamically allocated
**				 according to the size of the string-converted variadic argument
**				 it should store. Each time this buffer is full it will be
**				 reallocated with a double size. Increasing this size reduces
**				 the number of allocations and copies of memory but requires a
**				 heavier initial allocation only for some edge cases. A size of
**				 32 will be the best possible optimization to handle all the
**				 numeric variables that our function can receive as well as
**				 short strings (so it will handle most practical use cases
**				 without having any reallocation). Here I have set it to 4096
**				 (the virtual memory page size on my system) which is a good
**				 choice for the purpose of getting my project corrected by peers
**				 and moulinette. For more information about the special buffer
**				 please get a look at the below commentary @attribute:special_
**				 buffer.
*/

# define BUFFER_SIZE				1024
# define SPECIAL_BUFFER_START_SIZE	4096

/*
**	@brief: Object containing all necessary datas and pointers for the current
**			call of ft_printf().
**
**	@attributes:
**		format:	double pointer to the current computed char of the format str.
**		args:	va_list containing the variadic arguments.
**		f:		(flags):uint8_t containing all 6 possible flags of the project
**				(-0+# .). Each flag is represented by a byte defined below.
**		w:		(width): contains the user defined minimum width or 0 if
**				unspecified.
**		p:		(precision): contains the user defined precision if the dot flag
**				is present or 0 if unspecified.
**		sign:	stores the sign to be printed for a numerical argument so it can
**				be written to the buffer at the good moment (ie. before width if
**				the paddling char is '0'). This array can also store pointer and
**				hexadecimal predicates "0x" and "0X" for the same reason.
**		buffer:	contains characters to be printed for the next flush.
**		_n_*:	pointers to locations in the buffer. _n_current points to the
**				next byte to be written. There are four *_n_ pointers :
**					- _n_s : pointer to the beginning of the buffer ;
**					- _n_c : pointer to the next character of the buffer ;
**					- _n_save_c : save a position ;
**					- _n_e : pointer to the end of the buffer.
**		len:	total len printed since since ft_printf call. Incremented by
**				the difference between _n_current and _n_s when the buffer
**				is flushed.
**		special_buffer:	a specific buffer for handling right alignment without
**				having to calculate an argument len before writing it. In this
**				specific case, the argument will be first written to this buffer
**				and its len will be known by pointer difference. You can make
**				some optimizations by changing its starting size (see above
**				commentary about SPECIAL_BUFFER_START_SIZE for more information)
**		_s_*:	pointers to locations in the special buffer. _s_current points
**				to the next byte to be written. The difference between
**				_s_current and _s_start gives the len of the argument.
**					- _s_s : pointer to the beginning of the buffer ;
**					- _s_c : pointer to the next character of the buffer ;
**					- _s_e : pointer to the end of the buffer.
*/

typedef struct s_printer
{
	const char		**format;
	size_t			len;
	va_list			args;
	uint8_t			f;
	uint32_t		w;
	uint32_t		p;
	uint32_t		save_p;
	char			sign[3];
	char			buffer[BUFFER_SIZE];
	char			*_n_s;
	char			*_n_c;
	char			*_n_e;
	char			*_n_save_c;
	char			*special_buffer;
	uint32_t		_s_size;
	char			*_s_s;
	char			*_s_c;
	char			*_s_e;
	bool			malloc_error;
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
typedef void		(*t_func_handler)();

typedef struct s_handler
{
	t_func_handler	f;
	uint8_t			ignore;
}	t_handler;

char				*init_flags(const char **s, t_printer *printer);
void				reset_flags(t_printer *printer);
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
void				print_pre_width(long long offset, t_printer *p);
void				print_post_width(long long offset, t_printer *p);
void				realloc_special_buffer(t_printer *p);

#endif
