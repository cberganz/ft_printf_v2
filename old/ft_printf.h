/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:42:27 by cberganz          #+#    #+#             */
/*   Updated: 2021/12/02 15:37:08 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		is_arg(const char *s);
int		case_c(int c, int *len);
size_t	case_treatment(const char *s, va_list args, int *len);
size_t	case_text(const char *s, int *len);
void	case_i_d(int n, int *len);
void	case_s(char *s, int *len);
void	case_u(unsigned int n, int *len);
void	case_p(unsigned long nbr, int *len);
void	case_x(unsigned int nbr, int *len);
void	case_upperx(unsigned int nbr, int *len);

#endif
