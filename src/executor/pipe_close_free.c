/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_close_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:45:58 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/15 22:46:42 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Close all file descriptors
 * 
 */

void	close_all_fds(t_pipes *p)
{
	int	i;

	i = 0;
	while (i < p->num_cmd - 1)
	{
		close(p->fds[i][0]);
		close(p->fds[i][1]);
		i++;
	}
}

/*
 *
 * Free memory
 * Only free array memory for cmds
 * 
 */

void	free_pipeline(t_pipes *p)
{
	int	i;
	
	if (!p)
		return ;
	if (p->fds)
	{
		i = 0;
		while (i < p->num_cmd - 1)
			free(p->fds[i++]);
		free(p->fds);
	}
	free(p->cmds);
	free(p->pids);
	free(p);
}