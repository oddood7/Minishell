/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:59:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/25 19:34:52 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void    ft_free_lexer(t_lexer *list)
{
    t_lexer    *tmp;
    t_lexer    *next;

    if (!list)
        return ;
    tmp = list;
    while (tmp)
    {
        if (!tmp->next)
        {
            free(tmp->str);
            free(tmp);
            return ;
        }
        next = tmp->next;
        free(tmp->str);
        free(tmp);
        tmp = next;
    }
}

void	erreur_mall(t_main *mini)
{
	ft_free_tab(mini->env);
	mini->env = NULL;
	free(mini->input_line);
	ft_free_lexer(mini->lexer_list);
	mini->lexer_list = NULL;
	mini->cmd_parse = NULL;
	exit (1);
}