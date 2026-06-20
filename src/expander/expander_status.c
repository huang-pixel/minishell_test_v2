/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kexu <kexu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:25:38 by kexu              #+#    #+#             */
/*   Updated: 2026/04/29 12:25:39 by kexu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*status_slot(void)
{
	static int	status;

	return (&status);
}

int	get_last_status(void)
{
	return (*status_slot());
}

void	set_last_status(int status)
{
	*status_slot() = status;
}
