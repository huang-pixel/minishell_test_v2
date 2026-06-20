/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:33:11 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:55:34 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*lstnew
https://medium.com/@Dev_Frank/c-linked-list-singly-linked-list-12aecb168834
int	main(void)
{
	int		n = 42;
	t_list	*node = ft_lstnew(&n);

	printf("content: %d\n", *(int *)node->content);
	printf("next: %p\n", (void *)node->next);
	free(node);
	return (0);
}*/
