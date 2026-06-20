/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:07 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:26:08 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*new_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	node = new_ast_node(NODE_PIPE);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_pipeline(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipe_node;

	left = parse_primary(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == T_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_primary(cur);
		if (!right)
			return (free_one_ast(left));
		pipe_node = new_pipe_node(left, right);
		if (!pipe_node)
			return (free_two_ast(left, right));
		left = pipe_node;
	}
	return (left);
}
