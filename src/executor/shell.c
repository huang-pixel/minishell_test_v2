/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 23:50:44 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 19:18:33 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    cleanup_shell(t_shell *shell)
{
    if (!shell)
        return ;
    if (shell->node)
    {
        free_ast(shell->node);
        shell->node = NULL;
    }
    if (shell->tokens)
    {
        free_tokens(shell->tokens);
        shell->tokens = NULL;
    }
    if (shell->env)
        free_env(&shell->env);
}

int init_shell(t_shell *shell, char **envp)
{
    if (!shell)
        return (1);
    shell->env = init_env(envp);
    if (!shell->env)
        return (1);
    shell->node = NULL;
    shell->tokens = NULL;
    shell->last_status = 0;
    shell->main = 1;
    return (0);
}

void    set_shell_status(t_shell *shell, int status)
{
    if (shell)
        shell->last_status = status;
    set_last_status(status);
}

int get_shell_status(t_shell *shell)
{
    if (shell)
        return (shell->last_status);
    return (get_last_status());
}