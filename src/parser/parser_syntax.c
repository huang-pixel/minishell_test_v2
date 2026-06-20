/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:14 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:27:40 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_l_paren(t_token *token, int *depth)
{
	if (token->prev && token->prev->type != T_L_PAREN
		&& !syntax_is_binary_op(token->prev->type))
		return (print_unexpected(token->next));
	(*depth)++;
	if (token->next && token->next->type == T_R_PAREN)
		return (print_unexpected(token->next));
	return (1);
}

static int	check_r_paren(t_token *token, int *depth)
{
	if (--(*depth) < 0)
		return (print_unexpected(token));
	if (token->next && (token->next->type == T_WORD
			|| token->next->type == T_L_PAREN))
		return (print_unexpected(token->next));
	return (1);
}

static int	check_token(t_token *token, int *depth)
{
	if (token->type == T_L_PAREN)
		return (check_l_paren(token, depth));
	if (token->type == T_R_PAREN)
		return (check_r_paren(token, depth));
	if (token_is_redir(token->type))
		return (check_redir_target(token));
	if (syntax_is_binary_op(token->type) && (!token->prev || !token->next
			|| !syntax_is_cmd_start(token->next->type)
			|| syntax_is_binary_op(token->next->type)))
		return (print_unexpected(token->next));
	return (1);
}

int	check_syntax(t_token *tokens)
{
	int	depth;

	depth = 0;
	if (tokens && syntax_is_binary_op(tokens->type))
		return (print_unexpected(tokens));
	while (tokens)
	{
		if (!check_token(tokens, &depth))
			return (0);
		tokens = tokens->next;
	}
	if (depth != 0)
	{
		printf("syntax error: unclosed parenthesis\n");
		return (0);
	}
	return (1);
}
