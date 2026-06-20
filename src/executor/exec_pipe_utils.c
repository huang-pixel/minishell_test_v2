/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 00:41:24 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 18:16:37 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_cmds(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (count_cmds(node->left) + count_cmds(node->right));
	return (1);
}

void    free_fds(int **fds, int count)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (i < count)
	{
		if (fds[i])
		{
			close(fds[i][0]);
			close(fds[i][1]);
			free(fds[i]);
		}
		i++;
	}
	free(fds);
}

int	**generate_pipes(int num_pipes)
{
	int	i;
	int	**fds;

	i = 0;
	fds = malloc(sizeof(int *) * num_pipes);
	if (!fds)
		return (NULL);
	while (i < num_pipes)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			return (free_fds(fds, i), NULL);
		if (pipe(fds[i]) < 0)
		{
			free(fds[i]);
			fds[i] = NULL;
			return (free_fds(fds, i), perror("pipe"), NULL);
		}
		i++;
	}
	return (fds);
}

t_pipes *init_pipeline(t_ast *node)
{
    t_pipes *pipe;
    
    pipe = malloc(sizeof(t_pipes));
	if (!pipe)
		return (NULL);
	pipe->num_cmd = count_cmds(node);
	pipe->cmds = malloc(sizeof(t_ast *) * pipe->num_cmd);
	if (!pipe->cmds)
		return (free(pipe), NULL);
	pipe->pids = malloc(sizeof(pid_t) * pipe->num_cmd);
	if (!pipe->pids)
		return (free(pipe->cmds), free(pipe), NULL);
	pipe->fds = generate_pipes(pipe->num_cmd - 1);
	if (!pipe->fds)
		return (free(pipe->cmds), free(pipe->pids), free(pipe), NULL);
    return (pipe);
}

/*
 *
 * Walk the pipe node and collects all commands into a linear list
 * Suppose: ls | grep a | wc -l
 * This function fills:
 *   cmds[0] = AST(ls);
 *   cmds[1] = AST(grep a);
 *   cmds[2] = AST(wc -l);
 * t_ast **cmds has the same idea as char **argv
 * 
 */

void	collect_cmds(t_ast *node, t_ast **cmds, int *i)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		collect_cmds(node->left, cmds, i);
		collect_cmds(node->right, cmds, i);
	}
	else
	{
		cmds[*i] = node;
		(*i)++;
	}
}
