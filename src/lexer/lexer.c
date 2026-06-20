/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:00 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:26:01 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->quote = QUOTE_NONE;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	append_token(t_token **list, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return ;
	if (!*list)
	{
		*list = new_token;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new_token;
	new_token->prev = last;
}
