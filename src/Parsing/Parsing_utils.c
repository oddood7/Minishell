/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:26:11 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/16 22:44:53 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_lex(t_lexer *list)
{
	t_lexer		*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (tmp && tmp->operateur != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	init_parser_data(t_parsermain *data, \
t_lexer *list, t_main *mini)
{
	data->lexer_list = list;
	data->redirection = NULL;
	data->num_redir = 0;
	data->data = mini;
}

void	parse_addback(t_parsing **lst, t_parsing *new)
{
	t_parsing	*tmp;

	tmp = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
