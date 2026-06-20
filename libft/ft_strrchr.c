/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 01:08:39 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 22:43:07 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = NULL;
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			p = s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return ((char *)p);
}

/*strchr and strrchr
#include <stdio.h>

int	main(void)
{
	const char *str = "foo/bar/foobar.txt";
	char		target = '*';
	
	printf("%s\n", ft_strrchr(str, target));
	printf("%s\n", strrchr(str, target));
	return (0);
}*/
