/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 14:59:49 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/25 17:36:54 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_node(t_env *env, t_env **tab)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
}

t_env	**collect_items(t_env *env)
{
	int		count;
	t_env	**items_tab;

	count = count_env(env);
	items_tab = malloc(sizeof(t_env *) * (count + 1));
	if (!items_tab)
		return (NULL);
	fill_node(env, items_tab);
	return (items_tab);
}

void	sort_items(t_env **tab)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strncmp(tab[i]->key, tab[j]->key, INT_MAX) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_entry(t_env *node)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->key, STDOUT_FILENO);
	if (node->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(node->value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
