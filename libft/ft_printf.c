/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 00:54:56 by hhuang2           #+#    #+#             */
/*   Updated: 2026/03/04 17:51:43 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_format(char spec, va_list ap)
{
	if (spec == 'c')
		return (ft_print_char(va_arg(ap, int)));
	else if (spec == 's')
		return (ft_print_str(va_arg(ap, char *)));
	else if (spec == 'p')
		return (ft_print_hex((unsigned long long)va_arg(ap, void *),
				LOWER_CASE, spec));
	else if (spec == 'd' || spec == 'i')
		return (ft_print_nbr(va_arg(ap, int)));
	else if (spec == 'u')
		return (ft_print_unsigned(va_arg(ap, unsigned int)));
	else if (spec == 'x')
		return (ft_print_hex(va_arg(ap, unsigned int), LOWER_CASE, spec));
	else if (spec == 'X')
		return (ft_print_hex(va_arg(ap, unsigned int), UPPER_CASE, spec));
	else if (spec == '%')
		return (ft_print_char('%'));
	else
		return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		count;

	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	count = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			count += ft_get_format(*fmt, ap);
		}
		else
			count += ft_print_char(*fmt);
		fmt++;
	}
	va_end(ap);
	return (count);
}

/*#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	my_count, lib_count;
	char	*str = NULL;

	my_count = ft_printf("%p\n", (void *)INT_MAX);
	lib_count = printf("%p\n", (void *)INT_MAX);
	my_count = ft_printf("%s\n", str);
	lib_count = printf("%s\n", str);
	if (my_count == lib_count)
	{
		puts("OK! Test passed!");
		printf("%d\n%d\n", my_count, lib_count);
	}
	else
		puts("Bugs here.");
	return (0);
}*/
