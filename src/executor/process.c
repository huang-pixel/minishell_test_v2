/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:41:37 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/21 23:08:53 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * A execve parameters helper
 * 
 */

int	prepare_exec(char *exec, t_ast *node, t_shell *shell, t_exec_args *args)
{
	args->path = final_path(exec, shell->env);
	if (!args->path)
		return (path_error_status(exec));
	/*ft_putstr_fd("DEBUG path: ", 2);
	ft_putstr_fd(args->path ? args->path : "NULL", 2);
	ft_putstr_fd("\n", 2);*/
	args->argv = args_list(node->args);
	if (!args->argv)
		return (free(args->path), 1);
	args->envp = generate_tab(shell->env);
	if (!args->envp)
		return (free(args->path), free_words(args->argv), 1);
	return (0);
}

void	exec_child(char *exec, t_exec_args *args)
{
	execve(args->path, args->argv, args->envp);
	free(args->path);
	free_words(args->argv);
	free_words(args->envp);
	exit(path_error_status(exec));
}

int	exec_external(char *exec, t_ast *node, t_shell *shell, int pipe)
{
	pid_t		pid;
	t_exec_args	args;
	int			status;

	status = prepare_exec(exec, node, shell, &args);
	if (status)
		return (status);
	if (pipe)
		exec_child(exec, &args);
	pid = fork();
	if (pid == 0)
		exec_child(exec, &args);
	free(args.path);
	free_words(args.argv);
	free_words(args.envp);
	waitpid(pid, &status, 0);
	return (wait_status_code(status));
}

int	external_process(char *exec, t_ast *node, t_shell *shell, int pipe)
{
	int	status;

	status = handle_redirs(node->redirs);
	if (!status)
		status = exec_external(exec, node, shell, pipe);
	set_shell_status(shell, status);
	return (status);
}

/*
 *
 * This is for all builtins cmd execution
 * 
 */

int	exec_cmd_parent(char *exec, t_ast *node, t_shell *shell)
{
	int	fd_in;
	int	fd_out;
	int	status;
	
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	status = handle_redirs(node->redirs);
	if (!status)
		status = exec_builtin(exec, node, shell);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	set_shell_status(shell, status);
	return (status);
}