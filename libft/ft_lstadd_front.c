/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:41:38 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:56:37 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*lstadd_front
https://medium.com/@Dev_Frank/c-linked-list-singly-linked-list-12aecb168834
int	main(void)
{
	t_list	*head = NULL;
	t_list	*n1 = ft_lstnew("world");
	t_list	*n2 = ft_lstnew("hello");

	ft_lstadd_front(&head, n1);
	ft_lstadd_front(&head, n2);

	t_list	*tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}*/
