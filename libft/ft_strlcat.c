/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:16:07 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 17:36:20 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_size;
	size_t	s_size;

	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (size <= d_size)
		return (s_size + size);
	i = 0;
	while (src[i] && (d_size + i) < (size - 1))
	{
		dst[d_size + i] = src[i];
		i++;
	}
	dst[d_size + i] = '\0';
	return (d_size + s_size);
}

/*strlcat
int	main(void)
{
	char const	*s = "world!";
	char		d1[20], d2[20];
	size_t		my, lib;

	strcpy(d1, "Hello ");
	strcpy(d2, "Hello ");
	my = ft_strlcat(d1, "", 0);
	lib = strlcat(d2, "", 0);
	printf("Test:  ft=\"%s\" (%zu), std=\"%s\" (%zu)\n", d1, my, d2, lib);
	return (0);
}*/
