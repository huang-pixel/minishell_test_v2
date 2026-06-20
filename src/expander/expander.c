/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:31 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_ast(t_ast *node, char **envp)
{
	if (!node)
		return ;
	expand_ast(node->left, envp);
	expand_ast(node->right, envp);
	node->args = expand_args(node->args, envp);
	expand_redirs(node->redirs, envp);
}
