/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:26:11 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:04:01 by lde-mais         ###   ########.fr       */
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

int	check_all_help(t_main *mini, t_lexer *tmp, int len)
{
	if (len == 1 && !tmp->operateur)
	{
		if ((!ft_strncmp(tmp->str, "!", 1) || \
		!ft_strncmp(tmp->str, ":", 1)) && ft_strlen(tmp->str) == 1)
		{
			if (!ft_strncmp(tmp->str, "!", 1))
				mini->shell.error = handle_error_bis(1);
			else if (!ft_strncmp(tmp->str, ":", 1))
				mini->shell.error = handle_error_bis(0);
			return (1);
		}
		else if (!ft_strncmp(tmp->str, ".", 1) && ft_strlen(tmp->str) == 1)
		{
			mini->shell.error = handle_error_bis(2);
			return (1);
		}
		else if (!ft_strncmp(tmp->str, "..", 2) && ft_strlen(tmp->str) == 2)
		{
			mini->shell.error = handle_error_bis(127);
			return (1);
		}
	}
	return (0);
}
