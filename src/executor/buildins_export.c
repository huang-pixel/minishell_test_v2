/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 22:43:50 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 19:43:28 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_error_export(char *str)
{
    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/*
 *
 * Export can display all variables, even export without args
 * export TEST, should show TEST
 * this is where it differ from env
 * 
 */

static void print_export(t_env *env)
{
   while (env)
   {
    if (env->value)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(env->key, STDOUT_FILENO);
        ft_putchar_fd('=', STDOUT_FILENO);
        ft_putstr_fd("\"", STDOUT_FILENO);
        ft_putstr_fd(env->value, STDOUT_FILENO);
        ft_putstr_fd("\"", STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(env->key, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
     env = env->next;
   }
}

int extract_export(t_arg *arg, t_env **env)
{
    char    *key;
    char    *value;
    int     status;

    status = 0;
    while (arg)
    {
        key = extract_key(arg->value);
        value = extract_value(arg->value);
        if (!is_valid_key(key))
        {
            print_error_export(key);
            status = 1;
        }
        else
            set_env_val(env, key, value);
        free(key);
        free(value);
        arg = arg->next;
    }
    return (status); 
}

int exec_export(t_ast *node, t_env **env)
{
    t_arg   *arg;
    int     status;
    
    arg = node->args->next;
    if (!arg)
        return (print_export(*env), 0);
    status = extract_export(arg, env);
    return (status);
}

/*
 *
 * Export logic flow:
 * 1. without args, print env list, then stop
 * 2. with args, loop args, extract the key and value:
 * if key is invalid, print error and stop
 * otherwise, keep, update or create a new node
 * 3. free key and value, loop, finally return status
 * 
 */

/*int exec_export(t_env **env, t_ast *node)
{
    char    *key;
    char    *val;
    t_arg   *arg;
    int     status;

    arg = node->args->next;
    status = 0;
    if (!arg)
    {
        print_export(*env);
        return (status);
    }
    while (arg)
    {
        key = extract_key(arg->value);
        val = extract_value(arg->value);
        if (!is_valid_key(key))
        {
            ft_putstr_fd("export: invalid identifier\n", 2);
            status = 1;
        }
        else
            set_env_val(env, key, val);
        free(key);
        free(val);
        arg = arg->next;
    }
    return (status);
}*/