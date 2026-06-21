/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 23:39:28 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/21 01:58:58 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Grouping commands in parentheses create a subshell
 * The commands inside are executed in a child process
 * 
 */

int execute_subshell(t_ast *node, t_shell *shell)
{
    pid_t   pid;
    int     ret;
    int     status;
    
    pid = fork();
    if (pid < 0)
        return (perror("fork"), 1);
    if (pid == 0)
    {
        setup_child_signals();
        execute_ast(node->left, shell, 0);
    }
    setup_parent_wait_signals();
    waitpid(pid, &status, 0);
    setup_interactive_signals();
    ret = wait_status_code(status);
    set_shell_status(shell, ret);
    return (ret);
}