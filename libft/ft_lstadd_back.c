/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:59:57 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 20:17:25 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l_last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!lst || !new)
		return ;
	l_last = ft_lstlast(*lst);
	l_last->next = new;
}

/*lstadd_back
https://www.geeksforgeeks.org/dsa/insert-node-at-the-end-of-a-linked-list/
int	main(void)
{
	t_list	*head = NULL;
	t_list	*n1 = ft_lstnew("Break");
	t_list	*n2 = ft_lstnew("the");
	t_list	*n3 = ft_lstnew("code");
	t_list	*n4 = ft_lstnew(".");

	ft_lstadd_back(&head, n1);
	ft_lstadd_back(&head, n2);
	ft_lstadd_back(&head, n3);
	ft_lstadd_back(&head, n4);

	t_list	*tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
		return (0);
}*/
