/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:44:22 by corellan          #+#    #+#             */
/*   Updated: 2023/11/14 18:57:41 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_delete(t_list **lst, void **content, void (*del)(void *))
{
	if ((*content))
	{
		del((*content));
		(*content) = NULL;
	}
	ft_lstclear(&(*lst), del);
	(*lst) = NULL;
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy;
	t_list	*temp;
	t_list	*iter;
	void	*content;

	iter = lst;
	copy = (void *)0;
	temp = (void *)0;
	while (iter != (void *)0)
	{
		content = (*f)(iter->content);
		if (!content)
			return (ft_delete(&copy, &content, del));
		temp = ft_lstnew(content);
		if (!temp)
			return (ft_delete(&copy, &content, del));
		ft_lstadd_back(&copy, temp);
		iter = iter->next;
		temp = temp->next;
	}
	return (copy);
}
