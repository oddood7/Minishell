/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:59:29 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/22 21:50:05 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*new_lexer(t_main *mini, char *str, int operateur)
{
	t_lexer *new;
	static int i;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL); //fonction erreur malloc;
	new->str = str;
	new->operateur = operateur;
	new->i = i++;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_listadd(t_main *mini, char *str, t_operateurs operateur, t_lexer **lst)
{
	t_lexer *node;

	node = new_lexer(mini, str, operateur);
	if (!node)
		return (0);
	if (!lst)
		*lst = node;
	else
		ft_lstaddback(lst, node);
	return (1);
}

int	word_add_list(t_main *mini, char *str, int i, t_lexer **list)
{
	int j;
	char *tmp;

	if (count_double_quote(str, i) > 2 || count_simple_quote(str, i) > 2)
		j = get_to_quote(str, i);
	else
		j = different_get_to_quote(str, i, 0);
	if (j == 1)
	{
		tmp = ft_substr(str, i, j);
		if (!ft_listadd(mini, tmp, 0, list))
			return (free(tmp), -1);
		return (j);
	}
	tmp = ft_substr(str, i, j);
	if (!ft_listadd(mini, tmp, 0, list))
		return (free(tmp), -1);
	return (j);
}

int	do_lexer(t_main *mini)
{
	long unsigned int 	i;
	int					j;

	i = 0;
	while (mini->input_line[i])
	{
		j = 0;
		while (ft_whitespace(mini->input_line[i]))
			i++;
		if (mini->input_line[i] == '\0')
			break ;
		if (is_ope(data->input_line[i]))
			j = add_operateur(mini, mini->input_line, i, &mini->lexer_list);
		else
			j = word_add_list(data, data->input_line, i, &data->lexer_list);
		if (j < 0);
			return (0);
		i += j;
		if (i >= ft_strlen(data->input_line))
			break ;
	}
	return (1);
}
