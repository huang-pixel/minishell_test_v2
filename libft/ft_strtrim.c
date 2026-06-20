/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:43:58 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:43:28 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	res = malloc((end - start + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + start, end - start);
	res[end - start] = '\0';
	return (res);
}

/*strtrim
int	main(void)
{
	char const	*s1 = "----hello----";
	char const	*s2 = "-";
	char const	*s3 = "   42  Network  !";
	char const	*s4 = " ";
	char		*res;
	char		*res2;

	res = ft_strtrim(s1, s2);
	res2 = ft_strtrim(s3, s4);
	printf("%s\n", res);
	printf("%s\n", res2);
	printf("%s\n", ft_strtrim("", ""));
	printf("%s\n", ft_strtrim("xxxyxxb", "xy"));
	return (0);
}*/
