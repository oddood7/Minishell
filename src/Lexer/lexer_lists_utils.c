/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lists_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:04:52 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 15:07:05 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer *ft_delone(t_lexer **lst)
{
	if ((*lst)->str)
		(*lst)->str = NULL;
	*lst = NULL;
	return (NULL);
}

void	ft_lstaddback(t_lexer **lst, t_lexer *new)
{
	t_lexer *tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_delfirst(t_lexer **lst)
{
	t_lexer *tmp;

	tmp = *lst;
	
	*lst = tmp->next;
	ft_delone(&tmp);
	if (*lst)
		(*lst)->prev = NULL;
}

void	ft_delid(t_lexer **list, int id)
{
	t_lexer *tmp;
	t_lexer *prev;
	t_lexer *start;

	start = *list;
	tmp = start;
	if ((*list)->i == id)
	{
		ft_delfirst(list);
		return ;
	}
	while (tmp && tmp->i != id)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
		prev->next = tmp->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_delone(&tmp);
	*list = start;
}