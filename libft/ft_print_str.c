/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:01:06 by hhuang2           #+#    #+#             */
/*   Updated: 2026/03/04 17:53:18 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (ft_print_str("(null)"));
	while (*str != '\0')
	{
		ft_print_char((int)*str);
		str++;
		count++;
	}
	return (count);
}
