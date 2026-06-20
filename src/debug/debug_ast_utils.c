/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 00:00:00 by kexu              #+#    #+#             */
/*   Updated: 2026/05/03 00:00:00 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*debug_branch(int last)
{
	if (last)
		return ("`-");
	return ("|-");
}

void	debug_next_prefix(char *dst, char *src, int last)
{
	ft_strlcpy(dst, src, 1024);
	if (last)
		ft_strlcat(dst, "   ", 1024);
	else
		ft_strlcat(dst, "|  ", 1024);
}
