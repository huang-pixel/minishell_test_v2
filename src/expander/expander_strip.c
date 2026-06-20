/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_strip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:41 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:25:42 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*append_plain(char *dst, char *src)
{
	char	*joined;

	joined = ft_strjoin(dst, src);
	free(dst);
	free(src);
	return (joined);
}

static int	skip_quote(char *value, int *i, char *quote)
{
	if (!*quote && (value[*i] == '\'' || value[*i] == '"'))
	{
		*quote = value[*i];
		(*i)++;
		return (1);
	}
	if (*quote && value[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static char	*append_next_plain(char *out, char *value, int *i)
{
	char	*part;

	part = ft_substr(value, *i, 1);
	(*i)++;
	if (!part)
	{
		free(out);
		return (NULL);
	}
	return (append_plain(out, part));
}

char	*strip_quotes(char *value)
{
	char	*out;
	char	quote;
	int		i;

	out = ft_strdup("");
	quote = 0;
	i = 0;
	while (value && value[i] && out)
	{
		if (!skip_quote(value, &i, &quote))
			out = append_next_plain(out, value, &i);
	}
	return (out);
}
