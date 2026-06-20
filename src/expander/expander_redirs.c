/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_ambiguous_redir(t_redir *redir, char *new_file)
{
	char	**matches;
	int		ambiguous;

	if (redir->type == REDIR_HEREDOC || redir->quoted != QUOTE_NONE)
		return (0);
	if (has_blank(new_file))
		return (1);
	if (!has_unquoted_star(new_file))
		return (0);
	matches = expand_wildcard(new_file);
	ambiguous = (count_words(matches) > 1);
	free_words(matches);
	return (ambiguous);
}

static char	*expand_heredoc_file(t_redir *redir)
{
	if (redir->quoted == QUOTE_NONE && has_quotes(redir->file))
		redir->quoted = QUOTE_DOUBLE;
	return (ft_strdup(redir->file));
}

static char	*expand_redir_file(t_redir *redir, char **envp)
{
	if (redir->type == REDIR_HEREDOC)
		return (expand_heredoc_file(redir));
	if (redir->quoted == QUOTE_SINGLE)
		return (ft_strdup(redir->file));
	return (expand_value(redir->file, envp));
}

void	expand_redirs(t_redir *redirs, char **envp)
{
	char	*new_file;

	while (redirs)
	{
		new_file = expand_redir_file(redirs, envp);
		redirs->ambiguous = is_ambiguous_redir(redirs, new_file);
		free(redirs->file);
		redirs->file = new_file;
		redirs = redirs->next;
	}
}
