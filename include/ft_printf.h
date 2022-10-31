/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:33:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/31 19:55:26 by cberganz         ###   ########.fr       */
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
void	bufferize_string(char *s, t_func f);
void	bufferize_integer(unsigned long n, int base, char *base_str, t_func f);
void	bufferize_arg(void);
void	handle_illegal_argument(t_func f);
void	handle_percent(t_func f);
void	handle_char(t_func f);
void	handle_string(t_func f);
void	handle_pointer(t_func f);
void	handle_decimal(t_func f);
void	handle_unsigned(t_func f);
void	handle_hexadecimal_lower(t_func f);
void	handle_hexadecimal_upper(t_func f);

void	flags_construct(void);

#endif
