/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_primary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:10 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:26:11 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*attach_redirs(t_ast *node, t_token **cur)
{
	t_redir	*redir;

	while (*cur && token_is_redir((*cur)->type))
	{
		redir = parse_redir(cur);
		if (!redir)
		{
			free_ast(node);
			return (NULL);
		}
		append_redir(&node->redirs, redir);
	}
	return (node);
}

static t_ast	*new_subshell_node(t_ast *child)
{
	t_ast	*node;

	if (!child)
		return (NULL);
	node = new_ast_node(NODE_SUBSHELL);
	if (!node)
		return (NULL);
	node->left = child;
	return (node);
}

t_ast	*parse_subshell(t_token **cur)
{
	t_ast	*inner;
	t_ast	*node;

	if (!cur || !*cur || (*cur)->type != T_L_PAREN)
		return (NULL);
	*cur = (*cur)->next;
	inner = parse_logical(cur);
	if (!inner || !*cur || (*cur)->type != T_R_PAREN)
	{
		free_ast(inner);
		return (NULL);
	}
	*cur = (*cur)->next;
	node = new_subshell_node(inner);
	if (!node)
	{
		free_ast(inner);
		return (NULL);
	}
	return (attach_redirs(node, cur));
}

t_ast	*parse_primary(t_token **cur)
{
	if (*cur && (*cur)->type == T_L_PAREN)
		return (parse_subshell(cur));
	return (parse_command(cur));
}
