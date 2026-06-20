/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:24 by kexu              #+#    #+#             */
/*   Updated: 2026/06/06 19:45:02 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*new_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
}

int	token_is_redir(t_token_type type)
{
	return (type == T_LESS || type == T_GREAT
		|| type == T_DGREAT || type == T_DLESS);
}

t_arg	*append_arg(t_arg *args, char *value, t_quote_type quote)
{
	t_arg	*new_arg;
	t_arg	*last;

	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		return (NULL);
	new_arg->value = ft_strdup(value);
	if (!new_arg->value)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg->quote = quote;
	new_arg->next = NULL;
	if (!args)
		return (new_arg);
	last = args;
	while (last->next)
		last = last->next;
	last->next = new_arg;
	return (args);
}

t_redir	*new_redir(t_redir_type type, char *file, t_quote_type quoted)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->quoted = quoted;
	redir->ambiguous = 0;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

void	append_redir(t_redir **list, t_redir *new_redir)
{
	t_redir	*last;

	if (!new_redir)
		return ;
	if (!*list)
	{
		*list = new_redir;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_redir;
}
