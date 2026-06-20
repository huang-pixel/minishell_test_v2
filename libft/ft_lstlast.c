/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:54:11 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/18 23:58:22 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	l_size;

	if (!lst)
		return (NULL);
	l_size = ft_lstsize(lst);
	while (l_size > 1)
	{
		lst = lst->next;
		l_size--;
	}
	return (lst);
}

/*lstlast
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

	t_list	*last = ft_lstlast(head);
	printf("Last item: %s\n", (char *)last->content);
	return (0);
}*/
