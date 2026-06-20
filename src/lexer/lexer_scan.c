/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:53 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:25:54 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*operator_token(int *i, t_token_type type, char *value,
	int step)
{
	*i += step;
	return (new_token(type, value));
}

static t_token	*read_operator(char *input, int *i)
{
	if (input[*i] == '(')
		return (operator_token(i, T_L_PAREN, "(", 1));
	if (input[*i] == ')')
		return (operator_token(i, T_R_PAREN, ")", 1));
	if (input[*i] == '|' && input[*i + 1] == '|')
		return (operator_token(i, T_OR, "||", 2));
	if (input[*i] == '|' )
		return (operator_token(i, T_PIPE, "|", 1));
	if (input[*i] == '&' && input[*i + 1] == '&')
		return (operator_token(i, T_AND, "&&", 2));
	if (input[*i] == '&')
		return (NULL);
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (operator_token(i, T_DLESS, "<<", 2));
	if (input[*i] == '<')
		return (operator_token(i, T_LESS, "<", 1));
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (operator_token(i, T_DGREAT, ">>", 2));
	return (operator_token(i, T_GREAT, ">", 1));
}

static t_token	*next_token(char *input, int *i)
{
	if (input[*i] == '(' || input[*i] == ')' || input[*i] == '|'
		|| input[*i] == '&' || input[*i] == '<' || input[*i] == '>')
		return (read_operator(input, i));
	return (read_word_token(input, i));
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (input && input[i])
	{
		while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
			i++;
		if (!input[i])
			break ;
		token = next_token(input, &i);
		if (!token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		append_token(&tokens, token);
	}
	return (tokens);
}
