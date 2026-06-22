/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 18:48:26 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/22 17:23:08 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    close_saved_fds(t_shell *shell)
{
    if (shell->saved_stdin != -1)
    {
        dup2(shell->saved_stdin, STDIN_FILENO);
        dup2(shell->saved_stdout, STDOUT_FILENO);
        close(shell->saved_stdin);
        close(shell->saved_stdout);
        shell->saved_stdin = -1;
        shell->saved_stdout = -1;
    }
}

void    exit_free(char **args, t_shell *shell)
{
    free_words(args);
    cleanup_shell(shell);
    rl_clear_history();
}

void    exit_numeric_msg(char **args, t_shell *shell)
{
    ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    exit_free(args, shell);
    close_saved_fds(shell);
    exit(2);
}

void    exit_many_args(char **args, t_shell *shell)
{
    ft_putstr_fd("minishell: exit: too many arguments\n", 2);
    free_words(args);
    set_shell_status(shell, 1);
}