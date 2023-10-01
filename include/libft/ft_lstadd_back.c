/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:40:36 by lde-mais          #+#    #+#             */
/*   Updated: 2022/11/17 18:18:17 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*str;

	str = *lst;
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			str = ft_lstlast(*lst);
			str -> next = new;
		}
	}
}
