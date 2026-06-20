/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:05 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_ast_command(t_ast *node, char *next)
{
	print_ast_args(node->args, next, 0);
	print_ast_redirs(node->redirs, next, 1);
}

static void	print_ast_subshell(t_ast *node, char *prefix, char *next, int *id)
{
	print_ast_redirs(node->redirs, next, !node->left);
	if (node->left)
	{
		printf("%s`- body\n", next);
		debug_next_prefix(prefix, next, 1);
		print_ast_node(node->left, prefix, 1, id);
	}
}

static void	print_ast_binary(t_ast *node, char *prefix, char *next, int *id)
{
	if (node->left)
	{
		printf("%s%s left\n", next, debug_branch(!node->right));
		debug_next_prefix(prefix, next, !node->right);
		print_ast_node(node->left, prefix, 1, id);
	}
	if (node->right)
	{
		printf("%s`- right\n", next);
		debug_next_prefix(prefix, next, 1);
		print_ast_node(node->right, prefix, 1, id);
	}
}

void	print_ast_node(t_ast *node, char *prefix, int last, int *id)
{
	char	next[1024];

	if (!node)
		return ;
	printf("%s%s [%d] %s\n", prefix, debug_branch(last), ++(*id),
		debug_node_name(node->type));
	debug_next_prefix(next, prefix, last);
	if (node->type == NODE_CMD)
		print_ast_command(node, next);
	else if (node->type == NODE_SUBSHELL)
		print_ast_subshell(node, prefix, next, id);
	else
		print_ast_binary(node, prefix, next, id);
}

void	print_ast(t_ast *node, int level)
{
	static int	id;
	char		prefix[1024];

	(void)level;
	id = 0;
	prefix[0] = '\0';
	print_ast_node(node, prefix, 1, &id);
}
