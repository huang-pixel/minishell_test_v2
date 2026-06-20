/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_word_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|'
		|| c == '&' || c == '<' || c == '>' || c == '(' || c == ')');
}

t_quote_type	word_quote_type(char *word)
{
	int	len;
	int	i;
	int	has_quote;

	if (!word)
		return (QUOTE_NONE);
	len = ft_strlen(word);
	if (len >= 2 && word[0] == '\'' && word[len - 1] == '\'')
		return (QUOTE_SINGLE);
	if (len >= 2 && word[0] == '"' && word[len - 1] == '"')
		return (QUOTE_DOUBLE);
	i = 0;
	has_quote = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			has_quote = 1;
		i++;
	}
	if (has_quote)
		return (QUOTE_MIXED);
	return (QUOTE_NONE);
}

t_token	*finish_word_token(char *word)
{
	t_token	*token;

	token = new_token(T_WORD, word);
	if (token)
		token->quote = word_quote_type(word);
	free(word);
	return (token);
}
