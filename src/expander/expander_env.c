/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_var_char(char c)
{
	return (c == '_' || c == '?' || ft_isalnum(c));
}

char	*lookup_value(char *name, char **envp)
{
	int	len;

	if (!ft_strncmp(name, "?", 2))
		return (ft_itoa(get_last_status()));
	len = ft_strlen(name);
	while (envp && *envp)
	{
		if (!ft_strncmp(*envp, name, len) && (*envp)[len] == '=')
			return (ft_strdup(*envp + len + 1));
		envp++;
	}
	return (ft_strdup(""));
}

char	*expand_name(char *value, int *i, char **envp)
{
	int		start;
	char	*name;
	char	*out;

	start = *i + 1;
	*i = start;
	while (value[*i] && is_var_char(value[*i]))
		(*i)++;
	name = ft_substr(value, start, *i - start);
	if (!name)
		return (NULL);
	out = lookup_value(name, envp);
	free(name);
	return (out);
}
