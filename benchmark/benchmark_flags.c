/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:41:38 by cberganz          #+#    #+#             */
/*   Updated: 2022/11/10 01:08:37 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "ft_printf.h"

int	main(int argc, char *argv[])
{
	int	size;

	size = 0;
	while (size < 1)
	{
		printf("char:%-42c\n", 'c');
		printf("string:%-42.42s\n", "Hello");
		printf("pointer:%-42p\n", &size);
		printf("decimal:%+-42.42d\n", 42);
		printf("integer:%+-42.42i\n", -42);
		printf("unsigned:%-42.42u\n", 42);
		printf("hexa:%-#42.42x\n", 42);
		printf("hexa_upper:%-#42.42X\n", 42);
		printf("percent:%%\n");
		printf("char:%-42c string:%-42.42s pointer:%-42p decimal:%+-42.42d \
					integer:%+-42.42i unsigned:%-42.42u hexa:%-#42.42x \
					hexa_upper:%-#42.42X percent:%%", 'c', "Hello", 
					&size, 42, -42, 42, 42, 42);
		size++;
	}
	return (0);
}
