/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:53:41 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 16:09:11 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_w_dig(char *str, int i, int j)
{
	while (str[i + j] && !is_ope(str[i + j]))
	{
		if (str[i + j] == 34)
		{
			j++;
			while (str[i + j] != 34 && str[i + j])
				j++;
			j++;
			break ;
		}
		else if (str[i + j] == 39)
		{
			j++;
			while (str[i + j] != 39 && str[i + j])
				j++;
			j++;
			break ;
		}
		else
			j++;
	}
	return (j);
}

t_lexer	*new_lexer(t_main *mini, char *str, int operateur)
{
	t_lexer			*new;
	static int		i;

	(void)mini;
	new = (t_lexer *)ft_malloc(sizeof(t_lexer));
	new->str = str;
	new->operateur = operateur;
	new->i = i++;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
