/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:22:37 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 01:11:34 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Free t_env list
 * 
 */

void    free_env(t_env **env)
{
    t_env   *tmp;

    if (env == NULL)
        return ;
    while (*env)
    {
        tmp = (*env)->next;
        free((*env)->key);
        free((*env)->value);
        free(*env);
        *env = tmp;
    }    
}

/*
 *
 * Manually split up the envp variables
 * using strchr to find first '='
 * substr to return substring
 * envp = {"PATH=/bin", "USER=bob", ...}
 */

/*t_env	*init_env(char **envp)
{
	t_env *new;
	t_env *first;
	t_env *last;
	char *sep_idx;

	first = NULL;
	last = NULL;
	while (*envp)
	{
		sep_idx = ft_strchr(*envp, '=');
		if (sep_idx)
		{
			new = malloc(sizeof(t_env));
			new->key = ft_substr(*envp, 0, sep_idx - *envp);
			new->value = ft_strdup(sep_idx + 1);
			new->next = NULL;
			if (!first)
				first = new;
			else
				last->next = new;
			last = new;
		}
		envp++;
	}
	return (first);
}*/

t_env	*create_env(char *str, t_env **new)
{
	char	*sep_idx;
	
	*new = malloc(sizeof(t_env));
	if (!*new)
		return (NULL);
	(*new)->next = NULL;
	sep_idx = ft_strchr(str, '=');
	if (sep_idx)
	{
		(*new)->key = ft_substr(str, 0, sep_idx - str);
		(*new)->value = ft_strdup(sep_idx + 1);
	}
	else
	{
		(*new)->key = ft_strdup(str);
		(*new)->value = NULL;
	}
	if (!(*new)->key)
		return (free(*new), NULL);
	return ((*new));
}

t_env	*build_env(char **envp)
{
	t_env	*env;
	t_env	*head;
	t_env	*last;
	
	head = NULL;
	last = NULL;
	while (*envp)
	{
		env = create_env(*envp, &env);
		if (!env)
			return (free_env(&head), NULL);
		if (!head)
			head = env;
		else
			last->next = env;
		last = env;
		envp++;
	}
	return (head);
}