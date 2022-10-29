/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:33:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/30 00:11:22 by cberganz         ###   ########.fr       */
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

int		ft_printf(const char *s, ...);

Printer	*printer_singleton(void);

void	flush(void);
void	bufferize_char(char c);
void	bufferize_increment(void);
void	bufferize_string(char *s);
void	bufferize_integer(unsigned long n, int base, char *base_str);
void	bufferize_arg(void);
void	handle_illegal_argument(void);
void	handle_percent(void);
void	handle_char(void);
void	handle_string(void);
void	handle_pointer(void);
void	handle_decimal(void);
void	handle_unsigned(void);
void	handle_hexadecimal_lower(void);
void	handle_hexadecimal_upper(void);

void	flags_construct(void);

#endif
