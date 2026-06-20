/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	fill_new_match(char **new_matches, char **matches, char *value)
{
	int		i;

	i = 0;
	while (matches && matches[i])
	{
		new_matches[i] = matches[i];
		i++;
	}
	new_matches[i] = ft_strdup(value);
	if (!new_matches[i])
	{
		free(new_matches);
		return (0);
	}
	new_matches[i + 1] = NULL;
	return (1);
}

char	**append_match(char **matches, char *value)
{
	char	**new_matches;
	int		i;

	i = 0;
	while (matches && matches[i])
		i++;
	new_matches = malloc(sizeof(char *) * (i + 2));
	if (!new_matches)
		return (NULL);
	if (!fill_new_match(new_matches, matches, value))
		return (NULL);
	free(matches);
	return (new_matches);
}

static int	wildcard_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	sort_matches(char **matches)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (matches && matches[i])
	{
		j = i + 1;
		while (matches[j])
		{
			if (wildcard_strcmp(matches[i], matches[j]) > 0)
			{
				tmp = matches[i];
				matches[i] = matches[j];
				matches[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
