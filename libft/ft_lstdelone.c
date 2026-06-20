/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:09:00 by hhuang2           #+#    #+#             */
/*   Updated: 2025/11/19 20:19:49 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}

/*lstdelone
https://medium.com/@Dev_Frank/c-linked-list-singly-linked-list-12aecb168834
void	ft_delect(void *content)
{
	free(content);
}

int	main(void)
{
	char	*s1 = "heyheyhey";
	char	*s2 = ft_strdup(s1);
	t_list	*node = ft_lstnew(s2);

	printf("Before delecting: %s\n", (char *)node->content);
	ft_lstdelone(node, ft_delect);
	node = NULL;
	puts("Node delected.");
	return (0);
}*/
