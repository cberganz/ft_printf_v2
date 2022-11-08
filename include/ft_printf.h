/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:33:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/08 14:20:30 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "Printer.h"
# include "Flags.h"

# define B_RESET			0b00000000
# define B_MINUS_FLAG		0b00000001
# define B_ZERO_FLAG		0b00000010
# define B_DOT_FLAG			0b00000100
# define B_HASHTAG_FLAG		0b00001000
# define B_SPACE_FLAG		0b00010000
# define B_PLUS_FLAG		0b00100000
# define B_FLAG_SPECIFIER	0b00111111
# define B_FORMAT_SPECIFIER	0b11000000

int			ft_printf(const char *s, ...);

t_printer	*printer_singleton(void);

void		flush(t_printer *printer);
void		bufferize_char(char c, t_printer *printer);
void		special_bufferize_char(char c, t_printer *printer);
void		bufferize_increment(t_printer *printer);
void		bufferize_string(char *s, t_func f, t_printer *printer);
void		bufferize_integer(unsigned long n, int base, \
								char *base_str, t_func f, t_printer *printer);
void		bufferize_arg(t_printer *printer);
void		handle_illegal_argument(t_func f, t_printer *printer);
void		handle_percent(t_func f, t_printer *printer);
void		handle_char(t_func f, t_printer	*printer);
void		handle_string(t_func f, t_printer *printer);
void		handle_pointer(t_func f, t_printer *printer);
void		handle_decimal(t_func f, t_printer *printer);
void		handle_unsigned(t_func f, t_printer *printer);
void		handle_hexadecimal_lower(t_func f, t_printer *printer);
void		handle_hexadecimal_upper(t_func f, t_printer *printer);

void		print_width(long long offset, t_printer *printer);

void		flags_construct(void);

#endif
