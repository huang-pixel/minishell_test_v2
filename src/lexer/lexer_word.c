/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:56 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:27:04 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*join_parts(char *word, char *part)
{
	char	*joined;

	joined = ft_strjoin(word, part);
	free(word);
	free(part);
	return (joined);
}

static char	*read_plain_part(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != '\'' && input[*i] != '"'
		&& !is_word_delim(input[*i]))
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

static char	*read_quoted_part(char *input, int *i)
{
	char	quote;
	int		start;

	start = *i;
	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		if (quote == '\'')
			printf("syntax error: unclosed single quote\n");
		else
			printf("syntax error: unclosed double quote\n");
		return (NULL);
	}
	(*i)++;
	return (ft_substr(input, start, *i - start));
}

static char	*read_next_word_part(char *input, int *i)
{
	if (input[*i] == '\'' || input[*i] == '"')
		return (read_quoted_part(input, i));
	return (read_plain_part(input, i));
}

t_token	*read_word_token(char *input, int *i)
{
	char	*part;
	char	*word;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*i] && !is_word_delim(input[*i]))
	{
		part = read_next_word_part(input, i);
		if (!part)
		{
			free(word);
			return (NULL);
		}
		word = join_parts(word, part);
		if (!word)
			return (NULL);
	}
	return (finish_word_token(word));
}
