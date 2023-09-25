/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:59:29 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/25 19:31:28 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*new_lexer(t_main *mini, char *str, int operateur)
{
	t_lexer *new;
	static int i;

	(void)mini;
	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
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

	if (count_double_quote(str, i) > 2 || count_single_quote(str, i) > 2)
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

t_operateurs	is_ope(int c)
{
	int i;
	static int	tab_ope[3][2] = {
	{'|', PIPE},
	{'>', RIGHT},
	{'<', LEFT},
	};

	i = 0;
	while (i < 3)
	{
		if (tab_ope[i][0] == c)
			return (tab_ope[i][1]);
		i++;
	}
	return (0);
}

int	add_operateur(t_main *mini, char *str, int i, t_lexer **list)
{
	t_operateurs ope;

	ope = is_ope(str[i]);
	if (ope == RIGHT && is_ope(str[i + 1]) == RIGHT)
	{
		if(!ft_listadd(mini, NULL, RIGHT_RIGHT, list))
			return (-1);
		return (2);
	}
	else if (ope == LEFT && is_ope(str[i + 1]) == LEFT)
	{
		if (!ft_listadd(mini, NULL, LEFT_LEFT, list))
			return (-1);
		return (2);
	}
	else if (ope)
	{
		if (!ft_listadd(mini, NULL, ope, list))
			return (-1);
		return (1);
	}
	return (0);
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
		if (is_ope(mini->input_line[i]))
			j = add_operateur(mini, mini->input_line, i, &mini->lexer_list);
		else
			j = word_add_list(mini, mini->input_line, i, &mini->lexer_list);
		if (j < 0)
			return (0);
		i += j;
		if (i >= ft_strlen(mini->input_line))
			break ;
	}
	return (1);
}
