/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 01:06:52 by hhuang2           #+#    #+#             */
/*   Updated: 2026/03/04 01:06:59 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *
 * Deallocate the old data
 *
 */

void	deallocate(t_list_gnl **list)
{
	t_list_gnl	*aux;

	if (list == NULL)
		return ;
	while (*list != NULL)
	{
		aux = (*list)->next;
		free((*list)->str_read);
		free(*list);
		*list = aux;
	}
}

/*
 *
 * Find the last node
 *
 */

t_list_gnl	*find_last_node(t_list_gnl *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

/*
 *
 * Given the whole line length then return the content\n copy
 *
 */

void	str_dup(t_list_gnl *list, char *str)
{
	int	i;
	int	j;
	int	count_len;

	j = 0;
	if (list == NULL)
		return ;
	count_len = get_line_len(list);
	while (list)
	{
		i = 0;
		while (count_len > 0 && list->str_read[i])
		{
			str[j++] = list->str_read[i++];
			count_len--;
		}
		list = list->next;
	}
	str[j] = '\0';
}

/*
 *
 * Count the lengths per line: text\n
 *
 */

int	get_line_len(t_list_gnl *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_read[i])
		{
			if (list->str_read[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

/*
 *
 * Check if line has \n
 *
 */

char	*ft_strchr_gnl(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
