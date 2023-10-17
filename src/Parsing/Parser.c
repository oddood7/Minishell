/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:04:11 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 15:36:28 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_parsing	*parse_new(t_main *mini, char **tab, int redir, t_lexer *red)
{
	t_parsing *new;

	(void)mini;
	new = (t_parsing *)ft_malloc(sizeof(t_parsing));
	new->cmd_tab = tab;
	new->next = NULL;
	new->prev = NULL;
	new->doubl = 0;
	new->single = 0;
	new->redirection = red;
	new->num_redirection = redir;
	return (new);
}

t_parsing	*init_cmd(t_main *mini, t_parsermain *data, int n_word)
{
	char		**tab;
	t_lexer		*ongoing;
	t_parsing	*node;
	int			i;

	i = 0;
	redirections(mini, data);
	n_word = count_lex(data->lexer_list);
	tab = (char **)ft_malloc(sizeof(char *) * (n_word + 1));
	ongoing = data->lexer_list;
	while (n_word > 0)
	{
		if (ongoing->str)
		{
			tab[i] = ft_strdup(ongoing->str);
			ft_delid(&data->lexer_list, ongoing->i);
			ongoing = data->lexer_list;
			i++;
		}
		n_word--; 
	}
	tab[i] = 0;
	node = parse_new(mini, tab, data->num_redir, data->redirection);
	return (node);
}

int	parsing(t_main *mini)
{
	t_parsing		*node;
	t_parsermain	data;

	if (operateur_handle(mini) || check_all(mini))
		return (0);
	ft_memset(&data, 0, sizeof data);
	while (mini->lexer_list)
	{
		init_parser_data(&data, mini->lexer_list, mini);
		node = init_cmd(mini, &data, 0);
		if (!node)
			exit (1);
		if (!mini->cmd_parse)
			mini->cmd_parse = node;
		else
			parse_addback(&mini->cmd_parse, node);
		mini->lexer_list = data.lexer_list;
		if (mini->lexer_list && mini->lexer_list->operateur == PIPE)
			ft_delid(&mini->lexer_list, mini->lexer_list->i);
	}
	return (1);
}
