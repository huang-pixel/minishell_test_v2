/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 00:30:35 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/22 00:35:38 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Loop t_redir, since a single cmd can several redirections
 * If heredoc found, save fd[0] in t_redir->fd
 */

int   check_cmd_hd(t_ast *node)
{
    t_redir *tmp;

    tmp = node->redirs;
    while (tmp)
    {
        if (tmp->type == REDIR_HEREDOC)
        {
            tmp->fd = heredoc_child(tmp->file);
            if (tmp->fd < 0)
                return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

/*
 *
 * A recursive way to search heredoc
 * Check left and right side and return value
 * When it goes to PIPE, AND, OR and SUBSHELL call
 * Need to check the value return for each side
 * 
 */

int prepare_heredoc(t_ast *node)
{
    if (!node)
        return (0);
    if (node->type == NODE_CMD)
        return (check_cmd_hd(node));
    if (prepare_heredoc(node->left))
        return (1);
    if (prepare_heredoc(node->right))
        return (1);
    return (0);
}