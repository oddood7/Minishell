/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:37:14 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/05 23:37:45 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_rchar(char c, char v)
{
	if (c == v)
		return (1);
	return (0);
}

int ft_size_list(t_lexer *list)
{
	int i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void    resets(t_main *mini)
{
    if (mini->input_line)
        free(mini->input_line);
    if (mini->lexer_list)
        ft_free_lexer(mini->lexer_list);
    mini->lexer_list = NULL;
    if (mini->syntaxe_check == 0)
    {
        if (mini->cmd_parse)
            free_cmd_tab(mini);
        if (mini->cmd_parse)
            free_cmd_lst(mini->cmd_parse);
    }
    mini->syntaxe_check = 0;
    mini->cmd_parse = NULL;
}

void    free_kill(t_main *mini)
{
    ft_free_tab(mini->env);
    mini->env = NULL;
 	ft_free_tab(mini->env_exp);
    mini->env_exp = NULL;
}