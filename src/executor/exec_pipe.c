/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 16:13:20 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/22 01:29:39 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

	setup_parent_wait_signals();
	i = 0;
	while (i < p->num_cmd)
	{
		p->pids[i] = fork();
		if (p->pids[i] < 0)
		{
			perror("fork");
			while (i > 0)
				waitpid(p->pids[--i], NULL, 0);
			setup_interactive_signals();
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
	setup_interactive_signals();
	set_shell_status(shell, status);
	free_pipeline(p);
	return (status);
}
