/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:08:03 by corellan          #+#    #+#             */
/*   Updated: 2023/10/27 23:42:06 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if ((*lst) != (void *)0)
	{
		while ((*lst) != 0)
		{
			temp = ((*lst)->next);
			(*del)((*lst)->content);
			free((*lst));
			(*lst) = temp;
		}
	}
	else
		temp = (*lst);
}
