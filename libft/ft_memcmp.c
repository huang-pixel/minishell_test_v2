/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:26:27 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:03:43 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ps1;
	const unsigned char	*ps2;

	ps1 = s1;
	ps2 = s2;
	while (n > 0)
	{
		if (*ps1 != *ps2)
			return (*ps1 - *ps2);
		ps1++;
		ps2++;
		n--;
	}
	return (0);
}

/*memcmp
#include <stdio.h>

int	main(void)
{
	const char	*s1 = "Hello World!";
	const char	*s2 = "";
	int			mycmp;
	int			libcmp;

	mycmp = ft_memcmp(s1, s2, 0);
	libcmp = memcmp(s1, s2, 0);
	if (libcmp > 0)
		printf("%s is greater than %s\n", s1, s2);
	else if (libcmp < 0)
		printf("%s is greater than %s\n", s1, s2);
	else
		printf("%s is equal to %s\n", s1, s2);
	return (0);
}*/
