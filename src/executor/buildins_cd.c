/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:41:38 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 03:14:15 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *cd_path(t_ast *node, t_env **env)
{
    char    *path;

    if (node->args->next && node->args->next->next)
        return (ft_putstr_fd("cd: too many arguments\n", 2), NULL);
    if (!node->args->next || (node->args->next->value[0] == '~' &&
        node->args->next->value[1] == '\0'))
    {
        path = get_env_val(*env, "HOME");
        if (!path)
            return (ft_putstr_fd("cd: HOME not set\n", 2), NULL);
    }
    else if (node->args->next->value[0] == '-' &&
        node->args->next->value[1] == '\0')
    {
        path = get_env_val(*env, "OLDPWD");
        if (!path)
            return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
        ft_putstr_fd(path, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
        path = node->args->next->value;
    return (path);
}

int exec_cd(t_ast *node, t_env **env)
{
    char    *path;
    char    *newpwd;
    char    *oldpwd;

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (perror("getcwd"), 1);
    path = cd_path(node, env);
    if (!path)
        return (free(oldpwd), 1);
    if (chdir(path) < 0)
        return (perror("cd"), free(oldpwd), 1);
    newpwd = getcwd(NULL, 0);
    if (!newpwd)
        return (free(oldpwd), 1);
    set_env_val(env, "OLDPWD", oldpwd);
    set_env_val(env, "PWD", newpwd);
    free(oldpwd);
    free(newpwd);
    return (0);
}

/*int exec_cd(t_ast *node, t_env **env)
{
    int     flag;
    char    *path;
    char    *newpwd;
    char    *oldpwd;
    
    flag = 0;
    oldpwd = getcwd(NULL, 0);
    if ((no_arg(node)) || only_tilde(node))
    {
        path = get_env_val(*env, "HOME");
        if (!path)
        {
            free(oldpwd);
            return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
        }
    }
    else if (cd_oldpwd(node))
    {
        path = get_env_val(*env, "OLDPWD");
        if (!path)
        {
            free(oldpwd);
            return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
        }  
    }
    else if (tilde_path(node))
    {
        path = expand_cd_path(*env, node->args->next->value);
        flag = 1;
        if (!path)
        {
            free(oldpwd);
            return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
        }
    }
    else
        path = node->args->next->value;
    if (chdir(path) < 0)
    {
        free(oldpwd);
        if (flag)
            free(path);
        return (perror("cd"), 1);
    }
    newpwd = getcwd(NULL, 0);
    set_env_val(env, "OLDPWD", oldpwd);
    set_env_val(env, "PWD", newpwd);
    free(oldpwd);
    free(newpwd);
    if (flag)
        free(path);
    return (0);
}*/

/*int  no_arg(t_ast *node)
{
    return ((!node || !node->args || !node->args->next));
    
}

int  only_tilde(t_ast *node)
{
    char    *arg;

    arg = node->args->next->value;
    if (!ft_strncmp(arg, "~", 2))
        return (1);
    return (0);
}

int  cd_oldpwd(t_ast *node)
{
    char    *arg;
    
    arg = node->args->next->value;
    if (!ft_strncmp(arg, "-", 2))
        return (1);
    return (0);
}

int  tilde_path(t_ast *node)
{
    char    *arg;

    arg = node->args->next->value;
    if (arg[0] == '~' && arg[1] == '/')
        return (1);
    return (0);
}

char *expand_cd_path(t_env *env, char *value)
{
    char    *dir;
    char    *home;
    char    *expand;
    
    dir = ft_strchr(value, '/');
    if (!dir)
        return (NULL);
    home = get_env_val(env, "HOME");
    if (!home)
        return (NULL);
    expand = ft_strjoin(home, dir);
    if (!expand)
        return (NULL);
    return (expand);
}*/

/*static char *cd_get_path(t_ast *node, t_env *env)
{
    char    *arg;
    
    if (!node || !node->args || !node->args->next)
        return (get_env_val(env, "HOME"));
    arg = node->args->next->value;
    if (!ft_strncmp(arg, "~", 2))
        return (get_env_val(env, "HOME"));
    else if (!ft_strncmp(arg, "-", 2))
        return (get_env_val(env, "OLDPWD"));
    else if (arg[0] == '~' && arg[1] == '/')
        return (expand_cd_path(env, arg));
    return (arg);
}*/
