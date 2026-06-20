/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:00:28 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:16:53 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*p;

	if (num && size && (num > (size_t) - 1 / size))
		return (NULL);
	p = malloc(num * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, num * size);
	return (p);
}

/*calloc
#include <stdio.h>

int	main(void)
{
	size_t	n = 0;
	size_t	size = 0;
	void	*p1 = ft_calloc(n, size);
	void	*p2 = calloc(n, size);

	printf("My calloc(%zu, %zu) -> %p\n", n, size, p1);
	printf("calloc(%zu, %zu) -> %p\n", n, size, p2);
	free(p1);
	free(p2);
	return (0);
}*/
