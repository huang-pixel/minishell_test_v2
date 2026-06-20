/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 23:05:09 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 19:36:41 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Remove the node for unset
 * firstly, check if we have to delect the head node
 * if the input isn't head, we loop the left list to find the node
 * 
 */

void	delete_env_var(t_env **env, char *str)
{
    t_env   *curr;
    t_env   *prev;
    
    if (!env || !*env || !str)
        return ;
    curr = *env;
    prev = NULL;
    while (curr)
    {
        if (!ft_strncmp(curr->key, str, INT_MAX))
        {
            if (prev)
                prev->next = curr->next;
            else
                *env = curr->next;
            free(curr->key);
            free(curr->value);
            free(curr);
            return ;
        }
        prev = curr;
        curr = curr->next;
    }
}

/*void	delete_env_var(t_env **env, char *str)
{
	t_env	*curr;
	t_env	*pred;

	pred = *env;
	if (!ft_strncmp(pred->key, str, INT_MAX))
	{
		curr = pred->next;
		free(pred->key);
		free(pred->value);
		free(pred);
		*env = curr;
		return ;
	}
	curr = pred->next;
	while (curr)
	{
		if (!ft_strncmp(curr->key, str, INT_MAX))
		{
			pred->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			break ;
		}
		pred = curr;
		curr = curr->next;
	}
}*/

/*
 *
 * Find the last env linked list node
 * 
 */

t_env   *last_env_node(t_env *env)
{
    t_env   *tmp;
    t_env   *last;
    
    if (!env)
        return (NULL);
    tmp = env;
    while (tmp->next != NULL)
        tmp = tmp->next;
    last = tmp;
    return (last);
}

int  is_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int  ft_atol(char *str, long long *nb)
{
    long    res;
    int     sign;
    
    res = 0;
    sign = 1;
    while (*str == 32 || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        if (res > (LLONG_MAX - (*str - '0')) / 10)
            return (0);
        res = res * 10 + (*str - '0');
        str++;
    }
    *nb = res * sign;
    return (1);
}