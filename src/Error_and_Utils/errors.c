/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:59:00 by lde-mais          #+#    #+#             */
/*   Updated: 2023/09/27 00:47:10 by lde-mais         ###   ########.fr       */
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
	//a changer, marche pas comme prevu;
	ft_free_tab(mini->env);
	mini->env = NULL;
	free(mini->input_line);
	ft_free_lexer(mini->lexer_list);
	mini->lexer_list = NULL;
	mini->cmd_parse = NULL;
	exit (1);
}

int	directory_err(t_main *mini, char *str, int ok)
{
	ft_putstr_fd(str, 2);
	if (ok)
	{
		mini->return_value = 127;
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	else
	{
		mini->return_value = 126;
		ft_putstr_fd(" : Is directory\n", 2);
	}
	return (1);
}

int	handle_error(t_main *mini, char *str, int rv)
{
	ft_putendl_fd(str, 2);
	if (rv == 2)
		mini->return_value = 2;
	else if (rv == 127)
		mini->return_value = 127;
	else
		mini->return_value = rv;
	return (1);
}