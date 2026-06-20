/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 17:09:53 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/20 17:10:12 by hhuang2          ###   ########.fr       */
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