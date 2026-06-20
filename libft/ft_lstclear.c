/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:13:46 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 20:21:50 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*next_node;

	if (lst && del)
	{
		tmp = *lst;
		while (tmp)
		{
			next_node = tmp->next;
			del(tmp->content);
			free(tmp);
			tmp = next_node;
		}
		*lst = NULL;
	}
}

/*lstclear
https://medium.com/@Dev_Frank/c-linked-list-singly-linked-list-12aecb168834
void	ft_delect(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*head = NULL;
	head = ft_lstnew(ft_strdup("Break"));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("the")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("code")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup(".")));
	puts("Before clear: ");
	for (t_list	*tmp = head; tmp; tmp = tmp->next)
		printf("%s\n", (char *)tmp->content);
	puts("After clear: ");
	ft_lstclear(&head, ft_delect);
	if (head == NULL)
		puts("My list cleared finally.");
	else
		puts("Not cleared, some bugs here.");
	return (0);
}*/
