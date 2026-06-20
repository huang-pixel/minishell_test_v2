/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:49:01 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/07 00:17:33 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Handle redirections
 * 
 */

int	handle_redirs(t_redir *redirs)
{
    int fd;
    
    while (redirs)
    {
        fd = -1;
        if (redirs->ambiguous)
        {
            ft_putstr_fd("ambiguous redirect\n", 2);
            return (1);
        }
        if (redirs->type == REDIR_HEREDOC)
            fd = redirs->fd;
        else if (redirs->type == REDIR_IN)
            fd = open(redirs->file, O_RDONLY);
        else if (redirs->type == REDIR_OUT)
            fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (redirs->type == REDIR_APPEND)
            fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
            return (perror(redirs->file), 1);
        if (redirs->type == REDIR_HEREDOC || redirs->type == REDIR_IN)
        {
            if (dup2(fd, STDIN_FILENO) < 0)
                return (close(fd), perror("dup2"), 1);
        }
        else
        {
            if (dup2(fd, STDOUT_FILENO) < 0)
                return (close(fd), perror("dup2"), 1);
        }
        /*if (redirs->type == REDIR_IN && fd != STDIN_FILENO)
            close(fd);
        else if (redirs->type == REDIR_OUT && fd != STDOUT_FILENO)
            close(fd);*/
        if (fd != STDIN_FILENO && fd != STDOUT_FILENO)
            close(fd);
        redirs = redirs->next;
    }
	return (0);
}