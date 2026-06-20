/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:55:41 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 22:45:50 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if (uc == *(unsigned char *)s)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

/*strchr and strrchr
#include <stdio.h>

int	main(void)
{
	const char *str = "Try not. Do, or do not. There is no try.";
	char		target = '*';

	printf("%s\n", ft_strchr(str, target));
	printf("%s\n", strchr(str, target));
	return (0);
}*/
