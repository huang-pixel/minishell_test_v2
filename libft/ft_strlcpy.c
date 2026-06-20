/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 17:25:19 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*strlcpy
int	main(void)
{
	char const	*s = "Hello world!";
	char		d1[20], d2[20];
	size_t		my, lib;

	my = ft_strlcpy(d1, s, 0);
	lib = strlcpy(d2, s, 0);
	printf("Test:  ft=\"%s\" (%zu), std=\"%s\" (%zu)\n", d1, my, d2, lib);
	return (0);
}*/
