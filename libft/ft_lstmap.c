/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:48:35 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 20:27:44 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (content == NULL)
			return (ft_lstclear(&newlist, del), (NULL));
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			del(content);
			return (ft_lstclear(&newlist, del), (NULL));
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}

/*lstmap
void	delNode(void *p)
{
	free(p);
}

void	*contentIter(void *p)
{
	return (ft_strdup((char *)p));
}

int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew(ft_strdup("Break"));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("the")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("code")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(".")));
	t_list	*map = ft_lstmap(lst, contentIter, delNode);

	t_list	*tmp = map;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp ->next;
	}
	printf("NULL\n");
	ft_lstclear(&lst, delNode);
	ft_lstclear(&map, delNode);
	return (0);
}*/
