/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:04 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:26:05 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_node_type	logical_node_type(t_token_type type)
{
	if (type == T_AND)
		return (NODE_AND);
	return (NODE_OR);
}

static t_ast	*new_logical_node(t_token_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	node = new_ast_node(logical_node_type(type));
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_logical(t_token **cur)
{
	t_ast			*left;
	t_ast			*right;
	t_ast			*op_node;
	t_token_type	type;

	left = parse_pipeline(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == T_AND || (*cur)->type == T_OR))
	{
		type = (*cur)->type;
		*cur = (*cur)->next;
		right = parse_pipeline(cur);
		if (!right)
			return (free_one_ast(left));
		op_node = new_logical_node(type, left, right);
		if (!op_node)
			return (free_two_ast(left, right));
		left = op_node;
	}
	return (left);
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*tree;

	if (!check_syntax(tokens))
		return (NULL);
	tree = parse_logical(&tokens);
	if (!tree || tokens)
		return (free_one_ast(tree));
	return (tree);
}
