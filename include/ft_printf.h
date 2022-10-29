/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:33:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/29 05:41:49 by charles          ###   ########.fr       */
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

int	ft_printf(const char *s, ...);

Printer	*printer_restore();
void flush(void);
void bufferize_char(char c);
void bufferize_increment();
void bufferize_string(char *s);
void bufferize_integer(unsigned long n, int base, char *base_str);
void bufferize_arg();
void pass_argument();
void handle_percent();
void handle_char();
void handle_string();
void handle_pointer();
void handle_decimal();
void handle_unsigned();
void handle_hexadecimal_lower();
void handle_hexadecimal_upper();

Flags	*flags_construct();
static void	init(const char **s);
static void	reset(void);
static bool	is_flag_set(uint16_t flag);
static void	print_flags(void);

#endif
