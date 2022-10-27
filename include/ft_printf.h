/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:33:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/27 05:06:05 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "Printer.h"
# include "Flags.h"

# define B_RESET					0b0000000000000000
# define B_MINUS_FLAG				0b0000000000000001
# define B_ZERO_FLAG				0b0000000000000010
# define B_DOT_FLAG					0b0000000000000100
# define B_HASHTAG_FLAG				0b0000000000001000
# define B_SPACE_FLAG				0b0000000000010000
# define B_PLUS_FLAG				0b0000000000100000
# define B_FLAG_SPECIFIERS			0b0000000011111111
# define B_PERCENT_FLAG				0b0000000100000000
# define B_CHAR_FLAG				0b0000001000000000
# define B_STRING_FLAG				0b0000001100000000
# define B_POINTER_FLAG				0b0000010000000000
# define B_DECIMAL_FLAG				0b0000010100000000
# define B_INTEGER_FLAG				0b0000011000000000
# define B_UNSIGNED_DECIMAL_FLAG	0b0000011100000000
# define B_HEXADECIMAL_LOWER_FLAG	0b0000100000000000
# define B_HEXADECIMAL_UPPER_FLAG	0b0000100100000000
# define B_UNIMPLEMENTED			0b0000000000000000
# define B_FORMAT_SPECIFIER			0b1111111100000000

Printer	*printer_restore();
void flush(void);
void bufferize_char(char c);
void bufferize_string(char *s);
void bufferize_integer(unsigned long n, int base, char *base_str);
void bufferize_arg(va_list args, const char **s);
void pass_argument(va_list args);
void handle_percent(va_list args);
void handle_char(va_list args);
void handle_string(va_list args);
void handle_pointer(va_list args);
void handle_decimal(va_list args);
void handle_unsigned(va_list args);
void handle_hexadecimal_lower(va_list args);
void handle_hexadecimal_upper(va_list args);

Flags	*flags_construct();
static void	init(const char **s);
static void	reset(void);
static bool	is_flag_set(uint16_t flag);
static void	print_flags(void);

#endif
