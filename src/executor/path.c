/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:18 by hhuang2           #+#    #+#             */
/*   Updated: 2026/05/19 00:16:37 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Return exec path:
 * two cases: with or without '/'
 * 
 */

char	*final_path(char *exec, t_env *env)
{
	char	*path;
	
	if (ft_strchr(exec, '/'))
	{
		path = ft_strdup(exec);
		if (!path)
			return (NULL);
		if (access(path, X_OK) != 0)
			return (free(path), NULL);
	}
	else
	{
		path = build_path(exec, env);
		if (!path)
			return (NULL);
	}
	return (path);
}

/*
 *
 * If command doesn't have '/'
 * serach PATh directory to check if it exists
 *
 */

char	*build_path(char *exec, t_env *env)
{
	int		i;
	char	*add_slash;
	char	**val_list;
	char	*exec_path;

	val_list = get_val_list(env, "PATH");
	if (!val_list)
		return (NULL);
	i = -1;
	while (val_list[++i])
	{
		add_slash = ft_strjoin(val_list[i], "/");
		if (!add_slash)
			return (free_words(val_list), NULL);
		exec_path = ft_strjoin(add_slash, exec);
		free(add_slash);
		if (!exec_path)
			return (free_words(val_list), NULL);
		if (access(exec_path, X_OK) == 0)
			return (free_words(val_list), exec_path);
		free(exec_path);
	}
	free_words(val_list);
	return (NULL);
}

/*
 *
 * Convert "PATH" string value into an array
 * 
 */

char	**get_val_list(t_env *env, char *key)
{
	char	*val_str;
	char	**val_list;

	val_str = get_env_val(env, key);
	if (!val_str)
		return (NULL);
	val_list = ft_split(val_str, ':');
	if (!val_list)
		return (NULL);
	return (val_list);
}

/*
 *
 * This function is for getting "PATH" string value directly
 *
 */

char	*get_env_val(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, INT_MAX))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}