/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:07:11 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:54:39 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*striteri
void	upper_even(unsigned int i, char *s)
{
	if (i % 2 == 0 && *s >= 'a' && *s <= 'z')
		*s = *s - 32;
}

int	main(void)
{
	char	s1[] = "hello";
	char	s2[] = "42Network";
	char	s3[] = "";

	printf("Original: %s\n", s1);
	printf("Original: %s\n", s2);
	printf("Original: %s\n", s3);
	ft_striteri(s1, upper_even);
	ft_striteri(s2, upper_even);
	printf("After: %s\n", s1);
	printf("After: %s\n", s2);
	printf("After: %s\n", s3);
	return (0);
}*/
