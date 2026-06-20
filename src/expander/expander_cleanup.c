/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_quotes(char *value)
{
	while (value && *value)
	{
		if (*value == '\'' || *value == '"')
			return (1);
		value++;
	}
	return (0);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words && words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

void	free_arg_list(t_arg *args)
{
	t_arg	*next;

	while (args)
	{
		next = args->next;
		free(args->value);
		free(args);
		args = next;
	}
}

int	has_blank(char *value)
{
	while (value && *value)
	{
		if (*value == ' ' || (*value >= 9 && *value <= 13))
			return (1);
		value++;
	}
	return (0);
}

int	count_words(char **words)
{
	int	count;

	count = 0;
	while (words && words[count])
		count++;
	return (count);
}
