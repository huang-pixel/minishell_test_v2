/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:45 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:25:46 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*append_part(char *dst, char *src)
{
	char	*joined;

	joined = ft_strjoin(dst, src);
	free(dst);
	free(src);
	return (joined);
}

static char	*quote_part(char *value, int *i, char *quote)
{
	if (!*quote && (value[*i] == '\'' || value[*i] == '"'))
	{
		*quote = value[*i];
		(*i)++;
		return (ft_strdup(""));
	}
	if (*quote && value[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}

static char	*next_part(char *value, int *i, char *quote, char **envp)
{
	char	*part;

	part = quote_part(value, i, quote);
	if (part)
		return (part);
	if (value[*i] == '$' && *quote != '\'' && is_var_char(value[*i + 1]))
		return (expand_name(value, i, envp));
	part = ft_substr(value, *i, 1);
	(*i)++;
	return (part);
}

char	*expand_value(char *value, char **envp)
{
	char	*out;
	char	*part;
	char	quote;
	int		i;

	out = ft_strdup("");
	quote = 0;
	i = 0;
	while (value && value[i] && out)
	{
		part = next_part(value, &i, &quote, envp);
		if (!part)
		{
			free(out);
			return (NULL);
		}
		out = append_part(out, part);
	}
	return (out);
}
