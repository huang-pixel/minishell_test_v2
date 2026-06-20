/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:21:26 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 20:28:59 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

/*lstiter
https://medium.com/@Dev_Frank/c-linked-list-singly-linked-list-12aecb168834
https://stackoverflow.com/questions/11463514/
	  //using-loop-to-traverse-through-linked-list

void	printList(void *content)
{
	printf("%s\n", (char *)content);
}

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
	ft_lstiter(head, printList);
	printf("NULL\n");
}*/
