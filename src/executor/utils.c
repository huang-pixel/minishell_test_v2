/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:26:37 by hhuang2           #+#    #+#             */
/*   Updated: 2026/06/19 19:31:49 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *
 * Check first charater is alphanum or _ for unset and export
 * 
 */

int	is_valid_key(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


/*
 *
 * Function to verify if echo has "-n" option for echo
 * "-nn", "-nnnnn" are both valid
 * "-na" is not, "echo hello -n" neither
 * these two cases should print "-na", "hello -n"
 * 
 * 
*/

int	has_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

/*
 *
 * Counts the number of args
 *
 */

int	count_args(t_arg *args)
{
	int	count;

	count = 0;
	while (args)
	{
		count++;
		args = args->next;
	}
	return (count);
}

/*
 *
 * Converts char value in t_arg into array of args
 * args: ls, -a, wc, -l =>
 * argv = {"ls", "-l", NULL}...
 *
 */

char	**args_list(t_arg *args)
{
	int		i;
	int		count;
	char	**list;

	count = count_args(args);
	list = malloc(sizeof(char *) * (count + 1));
	if (!list)
		return (NULL);
	i = 0;
	while (args)
	{
		list[i] = ft_strdup(args->value);
		if (!list[i])
			return (free_words(list), NULL);
		i++;
		args = args->next;
	}
	list[i] = NULL;
	return (list);
}
