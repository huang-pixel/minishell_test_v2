/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	command_has_content(t_ast *cmd)
{
	return (cmd->args || cmd->redirs);
}

t_ast	*free_command(t_ast *cmd)
{
	free_ast(cmd);
	return (NULL);
}

char	*ast_word_value(t_token *token)
{
	if (!token)
		return (NULL);
	return (strip_quotes(token->value));
}

int	append_word_to_cmd(t_ast *cmd, t_token **cur)
{
	t_arg	*args;
	char	*value;

	value = ast_word_value(*cur);
	if (!value)
		return (0);
	args = append_arg(cmd->args, value, (*cur)->quote);
	free(value);
	if (!args)
		return (0);
	cmd->args = args;
	*cur = (*cur)->next;
	return (1);
}

int	append_redir_to_cmd(t_ast *cmd, t_token **cur)
{
	t_redir	*redir;

	redir = parse_redir(cur);
	if (!redir)
		return (0);
	append_redir(&cmd->redirs, redir);
	return (1);
}
