/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:10:53 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 22:59:42 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}

/*memchr
#include <stdio.h>

int	main(void)
{
	const char	s[8] = "abc\0def";
	char		*myres;
	char		*lib;

	myres = ft_memchr(s, '\0', 8);
	lib = memchr(s, '\0', 8);
	printf("%s", myres);
	printf("%s", lib);
	return (0);
}*/
