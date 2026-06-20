/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:18:04 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:27:58 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s + start, len);
	p[len] = '\0';
	return (p);
}

/*substr
int	main(void)
{
	char const	*s = "hello world";

	printf("%s", ft_substr(s, 12, 8));
	printf("%s", ft_substr(s, 5, 8));
	printf("%s", ft_substr("", 5, 8));
	return (0);
}*/
