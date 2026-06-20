/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:23:06 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 22:34:00 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char		*ps1;
	const unsigned char	*ps2;

	if (!s1 && !s2)
		return (NULL);
	if (s1 == s2 || n == 0)
		return (s1);
	ps1 = (unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	if (ps1 < ps2)
	{
		while (n--)
			*ps1++ = *ps2++;
	}
	else
	{
		ps1 += n;
		ps2 += n;
		while (n--)
			*--ps1 = *--ps2;
	}
	return (s1);
}

/*memove 
#include <stdio.h>

int	main(void)
{
	char	buf1[15] = "1234567";
	char	buf2[15] = "1234567";
	char	buf3[] = "";
	char	buf4[] = "";

	ft_memmove(buf1 + 4, buf1 + 2, 3);
	puts(buf1);
	memmove(buf2 + 4, buf2 + 2, 3);
	puts(buf2);
	ft_memmove(buf3, buf3, 0);
	puts(buf3);
	memmove(buf4, buf4, 0);
	puts(buf4);
	return (0);
}*/
