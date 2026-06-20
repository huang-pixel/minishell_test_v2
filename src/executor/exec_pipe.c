/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 16:13:20 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 03:28:11 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Return invalid path error status
 * 126 for permission, 127 when command not found
 * 1 for generic failure
 * 
 */

/*int	path_error_status(char *exec)
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
}*/

/*int	wait_status_code(int status)
{
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
}*/

/*void	exec_child(char *exec, t_ast *node, t_shell *shell)
{
	char	*path;
	char	**argv;
	char	**envp;
	
	path = final_path(exec, shell->env);
	if (!path)
		exit(path_error_status(exec));
	argv = args_list(node->args);
	if (!argv)
	{
		free(path);
		exit(1);
	}
	envp = generate_tab(shell->env);
	if (!envp)
	{
		free_words(argv);
		free(path);
		exit(1);
	}
	execve(path, argv, envp);
	perror(exec);
	free(path);
	free_words(argv);
	free_words(envp);
	exit(path_error_status(exec));
}*/

int	execute_pipe_child(t_pipes *p, int idx)
{
	int	i;
	
	setup_child_signals();
	p->shell->main = 0;
	if (idx > 0)
		if (dup2(p->fds[idx - 1][0], STDIN_FILENO) < 0)
			return (perror("dup2"), exit(1), 1);
	if (idx < p->num_cmd - 1)
		if (dup2(p->fds[idx][1], STDOUT_FILENO) < 0)
			return (perror("dup2"), exit(1), 1);
	i = 0;
	while (i < p->num_cmd - 1)
	{
		close(p->fds[i][0]);
		close(p->fds[i][1]);
		i++;
	}
	exit(execute_ast(p->cmds[idx], p->shell, 1));
}

/*
 *
 * Loop over commands and fork one child per command
 * Store each pid into pids array at index i
 * 
 * Fork failure zombie process:
 * If some processes have finished executing
 * But whose exit status has not been collected by parent
 * Parent should call waitpid 
 * And wait for every previously forked child
 * Before returning the error
 * 
 */

int	generate_fork(t_pipes *p)
{
	int	i;

	i = 0;
	while (i < p->num_cmd)
	{
		p->pids[i] = fork();
		if (p->pids[i] < 0)
		{
			perror("fork");
			while (i > 0)
				waitpid(p->pids[--i], NULL, 0);
			return (1);
		}
		if (p->pids[i] == 0)
			execute_pipe_child(p, i);
		i++;
	}
	return (0);
}

int	wait_pipe_status(t_pipes *p)
{
	int	i;
	int	status;
	
	i = 0;
	while (i < p->num_cmd)
	{
		waitpid(p->pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_pipe(t_ast *node, t_shell *shell)
{
	int		i;
	int		status;
	t_pipes	*p;
	
	p = init_pipeline(node);
	if (!p)
		return (1);
	p->shell = shell;
	i = 0;
	collect_cmds(node, p->cmds, &i);
	if (generate_fork(p))
	{
		close_all_fds(p);
		free_pipeline(p);
		return (1);
	}
	close_all_fds(p);
	status = wait_pipe_status(p);
	shell->last_status = status;
	free_pipeline(p);
	return (status);
}

/*int	execute_pipe(t_ast *node, t_env **env)
{
	int		fd[2];
	int		ret;
	pid_t	left;
	pid_t	right;
	int		status_l;
	int		status_r;

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	left = fork();
	if (left == 0)
	{
		setup_child_signals();
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(execute_ast(node->left, env, 1));
	}
	right = fork();
	if (right == 0)
	{
		setup_child_signals();
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		exit(execute_ast(node->right, env, 1));
	}
	close(fd[0]);
	close(fd[1]);
	setup_parent_wait_signals();
	waitpid(left, &status_l, 0);
	waitpid(right, &status_r, 0);
	setup_interactive_signals();
	ret = wait_status_code(status_r);
	set_last_status(ret);
	return (ret);
}*/

/*int	run_in_child(t_ast *node, int pipe)
{
	if (pipe)
		return (1);
	if (!node || !node->args)
		return (0);
	if (!is_builtin(node->args->value))
		return (1);
	return (0);
}*/
