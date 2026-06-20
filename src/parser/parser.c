/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:17 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:26:18 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_type	redir_type_from_token(t_token_type type)
{
	if (type == T_LESS)
		return (REDIR_IN);
	if (type == T_GREAT)
		return (REDIR_OUT);
	if (type == T_DGREAT)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

static int	redir_target_is_valid(t_token *token)
{
	return (token && token->type == T_WORD);
}

t_redir	*parse_redir(t_token **cur)
{
	t_redir			*redir;
	t_redir_type	type;
	char			*file;

	if (!cur || !*cur || !token_is_redir((*cur)->type))
		return (NULL);
	type = redir_type_from_token((*cur)->type);
	*cur = (*cur)->next;
	if (!redir_target_is_valid(*cur))
		return (NULL);
	file = ast_word_value(*cur);
	if (!file)
		return (NULL);
	redir = new_redir(type, file, (*cur)->quote);
	free(file);
	if (!redir)
		return (NULL);
	*cur = (*cur)->next;
	return (redir);
}

t_ast	*parse_command(t_token **cur)
{
	t_ast	*cmd;

	cmd = new_ast_node(NODE_CMD);
	if (!cmd)
		return (NULL);
	while (*cur && ((*cur)->type == T_WORD || token_is_redir((*cur)->type)))
	{
		if ((*cur)->type == T_WORD)
		{
			if (!append_word_to_cmd(cmd, cur))
				return (free_command(cmd));
		}
		else
		{
			if (!append_redir_to_cmd(cmd, cur))
				return (free_command(cmd));
		}
	}
	if (!command_has_content(cmd))
		return (free_command(cmd));
	return (cmd);
}
