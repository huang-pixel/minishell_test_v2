/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:26:50 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 19:22:07 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count += 1;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_extract(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (ft_substr(s, 0, len));
}

static void	ft_free_tab(char **seq)
{
	char	**ptr;

	if (!seq)
		return ;
	ptr = seq;
	while (*ptr != NULL)
		free(*(ptr++));
	free(seq);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			s_len;
	char		**seq;

	if (!s)
		return (NULL);
	s_len = ft_count(s, c);
	seq = ft_calloc((s_len + 1), sizeof(char *));
	if (!seq)
		return (NULL);
	i = 0;
	while (s_len > i)
	{
		while (*s == c)
			s++;
		seq[i] = ft_extract(s, c);
		if (!seq[i])
			return (ft_free_tab(seq), NULL);
		s += ft_strlen(seq[i]);
		i++;
	}
	seq[i] = NULL;
	return (seq);
}

/*split
static void	ft_free_tab(char **seq)
{
	int	i = 0;
	if (!seq)
		return ;
	while (seq[i])
	{
		free(seq[i]);
		i++;
	}
	free(seq);
}

static void	ft_result(char *s, char c)
{
	char **seq;
	int	i;

	seq = ft_split(s, c);
	if (!seq)
		return ;
	i = 0;
	while (seq[i])
	{
		printf("%s\n", seq[i]);
		i++;
	}
	printf("%d [NULL]\n", i);
	ft_free_tab(seq);
}

int	main(void)
{
	ft_result("", '*');
	puts("------------------\n");
	ft_result("***", '*');
	puts("------------------\n");
	ft_result("42 Network", '\0');
	puts("------------------\n");
	ft_result("hello  42  world  ", ' ');
	puts("------------------\n");
	return (0);
}*/
