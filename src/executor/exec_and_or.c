/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:48:44 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 19:46:32 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_and(t_ast *node, t_shell *shell)
{
    int status;

    status = execute_ast(node->left, shell, 0);
    if (!status)
        return (execute_ast(node->right, shell, 0));
    return (status);
}

int execute_or(t_ast *node, t_shell *shell)
{
    int status;

    status = execute_ast(node->left, shell, 0);
    if (status)
        return (execute_ast(node->right, shell, 0));
    return (status);
}