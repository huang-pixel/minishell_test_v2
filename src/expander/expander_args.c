/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_arg_value(t_arg *arg, char **envp)
{
	if (arg->quote == QUOTE_SINGLE)
		return (ft_strdup(arg->value));
	return (expand_value(arg->value, envp));
}

int	add_expanded_arg(t_arg **expanded, char *value, t_quote_type quote)
{
	t_arg	*new_list;

	new_list = append_arg(*expanded, value, quote);
	if (!new_list)
		return (0);
	*expanded = new_list;
	return (1);
}

static int	add_wildcard_args(t_arg **expanded, char **matches)
{
	int	j;

	j = 0;
	while (matches && matches[j])
	{
		if (!add_expanded_arg(expanded, matches[j], QUOTE_NONE))
			return (0);
		j++;
	}
	return (1);
}

static int	expand_one_arg(t_arg **expanded, t_arg *arg, char **envp)
{
	char	**matches;
	char	*new_value;
	int		ok;

	new_value = expand_arg_value(arg, envp);
	if (!new_value)
		return (0);
	matches = NULL;
	if (arg->quote == QUOTE_NONE && has_unquoted_star(new_value))
		matches = expand_wildcard(new_value);
	ok = add_wildcard_args(expanded, matches);
	if (ok && !matches)
		ok = add_expanded_arg(expanded, new_value, arg->quote);
	free(new_value);
	free_words(matches);
	return (ok);
}

t_arg	*expand_args(t_arg *args, char **envp)
{
	t_arg	*expanded;
	t_arg	*arg;

	expanded = NULL;
	arg = args;
	while (arg)
	{
		if (!expand_one_arg(&expanded, arg, envp))
		{
			free_arg_list(expanded);
			free_arg_list(args);
			return (NULL);
		}
		arg = arg->next;
	}
	free_arg_list(args);
	return (expanded);
}
