/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_is_binary_op(t_token_type type)
{
	return (type == T_PIPE || type == T_AND || type == T_OR);
}

int	syntax_is_cmd_start(t_token_type type)
{
	return (type == T_WORD || type == T_L_PAREN || token_is_redir(type));
}

char	*syntax_token(t_token *token)
{
	if (!token)
		return ("newline");
	if (token->type == T_PIPE)
		return ("|");
	if (token->type == T_AND)
		return ("&&");
	if (token->type == T_OR)
		return ("||");
	if (token->type == T_L_PAREN)
		return ("(");
	if (token->type == T_R_PAREN)
		return (")");
	if (token->type == T_LESS)
		return ("<");
	if (token->type == T_GREAT)
		return (">");
	if (token->type == T_DGREAT)
		return (">>");
	if (token->type == T_DLESS)
		return ("<<");
	return (token->value);
}

int	print_unexpected(t_token *token)
{
	printf("syntax error near unexpected token `%s`\n", syntax_token(token));
	return (0);
}

int	check_redir_target(t_token *token)
{
	if (!token->next || token->next->type != T_WORD)
		return (print_unexpected(token->next));
	return (1);
}
