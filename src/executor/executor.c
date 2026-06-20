/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 20:34:47 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 17:37:59 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * This function checks:
 * whether the input command is the same as builtin command
 * if ture, we have to implement it inside minishell
 * otherwise, we must create child process and use execve to run it
 *
 */

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

/*
 *
 * Turn into each builtin execution function
 * if receives unknown builtin or failed, return 1
 * 
 */

int	exec_builtin(char *exec, t_ast *node, t_shell *shell)
{
	if (!ft_strncmp(exec, "echo", 5))
		return (exec_echo(node));
	if (!ft_strncmp(exec, "cd", 3))
		return (exec_cd(node, &shell->env));
	if (!ft_strncmp(exec, "pwd", 4))
		return (exec_pwd());
	if (!ft_strncmp(exec, "export", 7))
		return (exec_export(node, &shell->env));
	if (!ft_strncmp(exec, "unset", 6))
		return (exec_unset(shell, node));
	if (!ft_strncmp(exec, "env", 4))
		return (exec_env(shell));
	if (!ft_strncmp(exec, "exit", 5))
		return (exec_exit(node, shell));
	return (0);
}

int	builtin_process(char *exec, t_ast *node, t_shell *shell)
{
	int	status;
	
	status = handle_redirs(node->redirs);
	if (!status)
		status = exec_builtin(exec, node, shell);
	set_shell_status(shell, status);
	return (status);
}

/*
 *
 * Divide minishell execution in two axes with 4 cases:
 * 
 *				    | in pipe  | not in pipe |
 * -----------------|----------|-------------|
 * builtin          |  case A  |   case B    |
 * external command |  case C  |   case D    |
 * 
 */

int	execute_cmd(t_ast *node, t_shell *shell, int pipe)
{
	char	*exec;

	if (!node->args)
		return (0);
	exec = node->args->value;
	if (is_builtin(exec))
	{
		if (pipe)
			return (builtin_process(exec, node, shell));
		return (exec_cmd_parent(exec, node, shell));
	}
	else
		return (external_process(exec, node, shell, pipe));
}

int	execute_ast(t_ast *node, t_shell *shell, int pipe)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (execute_cmd(node, shell, pipe));
	if (node->type == NODE_PIPE)
		return (execute_pipe(node, shell));
	/*if (node->type == NODE_AND)
		return (execute_and(node, shell));
	if (node->type == NODE_OR)
		return (execute_or(node, shell));
	if (node->type == NODE_SUBSHELL)
		return (execute_subshell(node, shell));*/
	return (1);
}