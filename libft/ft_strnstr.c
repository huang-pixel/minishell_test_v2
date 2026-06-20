/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:58:30 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:12:40 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	if (*s2 == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] && (i + j < len) && s2[j] && s1[i + j] == s2[j])
			j++;
		if (s2[j] == '\0')
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}

/*strnstr
#include <stdio.h>

int	main(void)
{
	char	*myres;
	char	*lib;

	myres = ft_strnstr("aaaaa", "b", 3);
	lib = strnstr("aaaaa", "b", 3);
	printf("%s\n", myres);
	printf("%s\n", lib);
	return (0);
}*/
