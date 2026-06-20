/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:49 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:25:50 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	match_pattern(char *pattern, char *name)
{
	if (!*pattern)
		return (!*name);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*name)
		{
			if (match_pattern(pattern, name))
				return (1);
			name++;
		}
		return (0);
	}
	if (*name && *pattern == *name)
		return (match_pattern(pattern + 1, name + 1));
	return (0);
}

int	has_unquoted_star(char *value)
{
	char	quote;

	quote = 0;
	while (value && *value)
	{
		if (!quote && (*value == '\'' || *value == '"'))
			quote = *value;
		else if (quote && *value == quote)
			quote = 0;
		else if (!quote && *value == '*')
			return (1);
		value++;
	}
	return (0);
}

static int	should_match(char *pattern, char *name)
{
	if (name[0] == '.' && pattern[0] != '.')
		return (0);
	return (match_pattern(pattern, name));
}

static int	add_dir_match(char *pattern, char ***matches, char *name)
{
	char	**tmp;

	if (!should_match(pattern, name))
		return (1);
	tmp = append_match(*matches, name);
	if (!tmp)
		return (0);
	*matches = tmp;
	return (1);
}

char	**expand_wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**matches;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	ent = readdir(dir);
	while (ent)
	{
		if (!add_dir_match(pattern, &matches, ent->d_name))
		{
			closedir(dir);
			return (NULL);
		}
		ent = readdir(dir);
	}
	closedir(dir);
	sort_matches(matches);
	return (matches);
}
