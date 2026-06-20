/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:59:57 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:53:40 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	new_s = malloc((s_len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (i < s_len)
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

/*strmapi
char	add_index(unsigned int i, char c)
{
	return (c + i);
}

int	main(void)
{
	char const	*s = "abcdef";

	printf("%s", ft_strmapi(s, add_index));
	printf("%s", ft_strmapi("", add_index));
	return (0);
}*/
