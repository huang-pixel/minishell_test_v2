/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:26:20 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:26:21 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*token_name(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_AND)
		return ("AND");
	if (type == T_OR)
		return ("OR");
	if (type == T_L_PAREN)
		return ("L_PAREN");
	if (type == T_R_PAREN)
		return ("R_PAREN");
	if (type == T_LESS)
		return ("LESS");
	if (type == T_GREAT)
		return ("GREAT");
	if (type == T_DGREAT)
		return ("DGREAT");
	return ("DLESS");
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("[%s:%s]", token_name(tokens->type), tokens->value);
		if (tokens->next)
			printf(" ");
		tokens = tokens->next;
	}
	printf("\n");
}
