/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_ast_args(t_arg *args, char *prefix, int last)
{
	int		i;
	char	next[1024];

	if (!args)
	{
		printf("%s%s args: (none)\n", prefix, debug_branch(last));
		return ;
	}
	printf("%s%s args\n", prefix, debug_branch(last));
	debug_next_prefix(next, prefix, last);
	i = 0;
	while (args)
	{
		printf("%s%s [%d] value=%s quoted=%s\n", next,
			debug_branch(!args->next), i, args->value,
			debug_quote_name(args->quote));
		args = args->next;
		i++;
	}
}

void	print_ast_redirs(t_redir *redirs, char *prefix, int last)
{
	char	next[1024];

	if (!redirs)
	{
		printf("%s%s redirs: (none)\n", prefix, debug_branch(last));
		return ;
	}
	printf("%s%s redirs\n", prefix, debug_branch(last));
	debug_next_prefix(next, prefix, last);
	while (redirs)
	{
		printf("%s%s {type=%s file=%s quoted=%s ambiguous=%d}\n", next,
			debug_branch(!redirs->next), debug_redir_name(redirs->type),
			redirs->file, debug_quote_name(redirs->quoted),
			redirs->ambiguous);
		redirs = redirs->next;
	}
}
