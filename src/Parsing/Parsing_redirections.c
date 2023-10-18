/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:51:19 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/18 15:51:36 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input_redir(t_main *mini, t_lexer *tmp, t_parsermain *data)
{
	char	*file;
	t_lexer	*new;
	int		id;
	int		id2;

	file = ft_strdup(tmp->next->str);
	id = tmp->i;
	id2 = tmp->next->i;
	new = new_lexer(mini, file, tmp->operateur);
	if (!new)
	{
		free_garbage();
		exit(1);
	}
	if (!data->redirection)
		data->redirection = new;
	else
		ft_lstaddback(&data->redirection, new);
	ft_delid(&data->lexer_list, id);
	ft_delid(&data->lexer_list, id2);
	data->num_redir++;
}

void	redirections(t_main *mini, t_parsermain *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp && !tmp->operateur)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (tmp->operateur)
	{
		if (tmp->operateur == PIPE)
			return ;
		else
			input_redir(mini, tmp, data);
	}
	redirections(mini, data);
}
