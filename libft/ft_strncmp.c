/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 01:56:35 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 22:55:11 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*strncmp
#include <stdio.h>

int	main(void)
{
	const char	*s1 = "Hello World!";
	const char	*s2 = "";
	int			mycmp;
	int			libcmp;

	mycmp = ft_strncmp(s1, s2, 0);
	libcmp = strncmp(s1, s2, 0);
	if (mycmp > 0)
		printf("%s is greater than %s\n", s1, s2);
	else if (mycmp < 0)
		printf("%s is greater than %s\n", s1, s2);
	else
		printf("%s is equal to %s\n", s1, s2);
	return (0);
}*/
