/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:26:46 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 18:11:54 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	if (!d && !s)
		return (NULL);
	if (d == s || n == 0)
		return (d);
	pd = d;
	ps = s;
	while (n-- > 0)
		*pd++ = *ps++;
	return (d);
}

/*memcpy
#include <stdio.h>

int	main(void)
{
	const char	*src = "Hello";
	char dest[10];

	strcpy(dest,"xxxxx");
	printf("Before memcpy dest = %s\n", dest);
	ft_memcpy(dest, src, 0);
	printf("After memcpy dest = %s\n", dest);
	return(0);
}*/
