/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast_names.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*debug_node_name(t_node_type type)
{
	if (type == NODE_CMD)
		return ("CMD");
	if (type == NODE_PIPE)
		return ("PIPE");
	if (type == NODE_AND)
		return ("AND");
	if (type == NODE_OR)
		return ("OR");
	return ("SUBSHELL");
}

char	*debug_redir_name(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("IN");
	if (type == REDIR_OUT)
		return ("OUT");
	if (type == REDIR_APPEND)
		return ("APPEND");
	return ("HEREDOC");
}

char	*debug_quote_name(t_quote_type quote)
{
	if (quote == QUOTE_SINGLE)
		return ("single");
	if (quote == QUOTE_DOUBLE)
		return ("double");
	if (quote == QUOTE_MIXED)
		return ("mixed");
	return ("none");
}
