/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 19:35:43 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 19:42:31 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Append a new node based on given env list
 * 
 */

void    append_new_node(t_env **env, char *key, char *val)
{
    t_env   *last;
    t_env   *new_node;
    
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return ;
    new_node->key = ft_strdup(key);
    if (val)
        new_node->value = ft_strdup(val);
    else
        new_node->value = NULL;
    new_node->next = NULL;
    if (*env == NULL)
    {
        *env = new_node;
        return ;
    }
    last = last_env_node(*env);
    last->next = new_node;
}

/*
 *
 * Export:
 * if key found: 
 * without new value, just keep old value, stop and no update
 * with new value, we should update the value
 * if key not found: 
 * create a new node then append it based on given env list
 * 
 */

void    set_env_val(t_env **env, char *key, char *val)
{
    t_env   *tmp;

    tmp = *env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
        {
            if (val)
            {
                free(tmp->value);
                tmp->value = ft_strdup(val);
            }
            return ;
        }
        tmp = tmp->next;
    }
    append_new_node(env, key, val);
}

/*
 *
 * Get the key pattern from the command line
 * export TEST, export TEST=42, or just export all valid
 * 
 */

char *extract_key(char *str)
{
    char    *tmp;
    char    *key;

    if (str)
    {
        tmp = ft_strchr(str, '=');
        if (tmp)
        {
            key = ft_substr(str, 0, tmp - str);
            if (!key)
                return (NULL);
            return (key);
        }
        key = ft_strdup(str);
        if (!key)
            return (NULL);
        return (key);
    }
    else
        return (NULL);
}

/*
 *
 * Value can be NULL, export TEST is valid behavior
 * if export TEST=, value = "", empty string is also valid
 * 
 */

char    *extract_value(char *str)
{
    char    *tmp;
    char    *value;

    if (str)
    {
        tmp = ft_strchr(str, '=');
        if (tmp)
        {
            value = ft_strdup(tmp + 1);
            if (!value)
                return (NULL);
            return (value);
        }
        return (NULL);
    }
    else
        return (NULL);
}
