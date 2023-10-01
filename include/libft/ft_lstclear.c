/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:04:52 by lde-mais          #+#    #+#             */
/*   Updated: 2022/11/17 18:18:39 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*str;
	t_list	*temp;

	if (!lst || !del)
		return ;
	str = *lst;
	while (str != NULL)
	{
		temp = str -> next;
		ft_lstdelone(str, del);
		str = temp;
	}
	*lst = NULL;
}
