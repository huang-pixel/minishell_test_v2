/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:41:37 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 16:48:14 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * This function is for a single external command with fork
 * Ex: ls, cat, ...
 * 
 */

/*int	exec_cmd_external(t_ast *node, t_env **env)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		setup_child_signals();
		exec_cmd_child(node, env);
	}
	setup_parent_wait_signals();
	waitpid(pid, &status, 0);
	setup_interactive_signals();
	ret = wait_status_code(status);
	set_last_status(ret);
	return (ret);
}*/

/*
 *
 * Return invalid path error status
 * 126 for permission, 127 when command not found
 * 1 for generic failure
 * 
 */

int	path_error_status(char *exec)
{
	if (errno == EACCES)
	{
		perror(exec);
		return (126);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(exec, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	perror(exec);
	return (1);
}

int	wait_status_code(pid_t pid)
{
	int	status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

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
	args->argv = args_list(node->args);
	if (!args->argv)
		return (free(args->path), 1);
	args->envp = generate_tab(shell->env);
	if (!args->envp)
		return (free(args->path), free_words(args->argv), 1);
	return (0);
}

void	exec_child(char *exec, char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	perror(exec);
	free(path);
	free_words(argv);
	free_words(envp);
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
		exec_child(exec, args.path, args.argv, args.envp);
	pid = fork();
	if (pid == 0)
		exec_child(exec, args.path, args.argv, args.envp);
	free(args.path);
	free_words(args.argv);
	free_words(args.envp);
	return (wait_status_code(pid));
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
 * This function is just for execution, not fork
 * in pipe or external child processus
 * Ex: ls, export | wc -l
 */

/*int	exec_cmd_child(t_ast *node, t_env **env)
{
	char	*exec;
	int		status;

	if (!node || !node->args)
		exit(0);
	exec = node->args->value;
	status = handle_redirs(node->redirs);
	if (status)
		exit(status);
	if (is_builtin(exec))
		exit(exec_builtin(node, env));
	exec_external_child(exec, node, *env);
	exit(1);
}*/

/*
 *
 * execve needs path, argv, and envp
 * char *path = "/bin/ls", char **argv = {"ls", "-l", NULL}
 * char **envp = {"PATH=/bin"}
 * 
 */

/*int	exec_external(char *exec, t_ast *node, t_env *env)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		status;
	char	*path;
	char	**argv;
	char	**envp;

	if (!exec || !*exec)
		return (127);
	path = final_path(exec, env);
	if (!path)
		return (path_error_status(exec));
	argv = args_list(node->args);
	if (!argv)
	{
		free(path);
		return (1);
	}
	envp = generate_tab(env);
	if (!envp)
	{
		free_words(argv);
		free(path);
		return (1);
	}
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	status = handle_redirs(node->redirs);
	if (status)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
		free(path);
		free_words(argv);
		free_words(envp);
		return (status);
	}
	pid = fork();
	if (pid < 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
		perror("fork");
		free(path);
		free_words(argv);
		free_words(envp);
		return (1);
	}
	if (pid == 0)
	{
		close(fd_in);
		close(fd_out);
		setup_child_signals();
		execve(path, argv, envp);
		perror(exec);
		free(path);
		free_words(argv);
		free_words(envp);
		exit(path_error_status(exec));
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	setup_parent_wait_signals();
	waitpid(pid, &status, 0);
	setup_interactive_signals();
	free(path);
	free_words(argv);
	free_words(envp);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (1);
}*/
