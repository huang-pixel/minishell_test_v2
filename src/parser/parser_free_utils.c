/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*free_one_ast(t_ast *node)
{
	free_ast(node);
	return (NULL);
}

t_ast	*free_two_ast(t_ast *left, t_ast *right)
{
	free_ast(left);
	free_ast(right);
	return (NULL);
}
