/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:57:22 by hhuang2           #+#    #+#             */
/*   Updated: 2026/03/04 17:52:44 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned long long n, char *sym, char spec)
{
	int		count;
	size_t	base_len;

	count = 0;
	if (spec == 'p')
	{
		if (!n)
			return (ft_print_str("(nil)"));
		else
		{
			count += ft_print_str("0x");
			spec = 'x';
		}
	}
	base_len = ft_strlen(sym);
	if (n < base_len)
		count += ft_print_char(sym[n]);
	else
	{
		count += ft_print_hex(n / base_len, sym, spec);
		count += ft_print_hex(n % base_len, sym, spec);
	}
	return (count);
}
