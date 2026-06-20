/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:48:01 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:57:25 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*lstsize
int	main(void)
{
	t_list	*head = NULL;
	t_list	*n1 = ft_lstnew("!");
	t_list	*n2 = ft_lstnew("42");
	t_list	*n3 = ft_lstnew("World");
	t_list	*n4 = ft_lstnew("Hello");

	ft_lstadd_front(&head, n1);
	ft_lstadd_front(&head, n2);
	ft_lstadd_front(&head, n3);
	ft_lstadd_front(&head, n4);

	int	len = ft_lstsize(head);
	printf("My linked list size is: %d\n", len);
	return (0);
}*/
