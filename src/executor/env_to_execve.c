/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:46:40 by hhuang2           #+#    #+#             */
/*   Updated: 2026/05/19 00:09:10 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t  count_env(t_env *env)
{
    size_t  len;
    
    len = 0;
    while (env)
    {
        len++;
        env = env->next;
    }
    return (len);
}

/*
 *
 * Return one sigle env variable
 * ret = "PATH=/bin"
 * 
 */

char    *get_single_str(t_env *env)
{
    char    *tmp;
    char    *ret;
    
    tmp = ft_strjoin(env->key, "=");
    if (!tmp)
        return (NULL);
    ret = ft_strjoin(tmp, env->value);
    free(tmp);
    if (!ret)
        return (NULL);
    return (ret);
}

/*
 *
 * Generate the envp arrary
 * count lenghth, use calloc filling NULL pointer
 * if value is NULL, skip
 * 
 */

char    **generate_tab(t_env *env)
{
    int     i;
    char    **tab;

    tab = ft_calloc(count_env(env) + 1, sizeof(char *));
    if (!tab)
        return (NULL);
    i = 0;
    while (env)
    {
        if (env->value)
        {
            tab[i] = get_single_str(env);
            if (!tab[i])
                return (free_words(tab), NULL);
            i++;
        }
        env = env->next;
    }
    tab[i] = NULL;
    return (tab);
}