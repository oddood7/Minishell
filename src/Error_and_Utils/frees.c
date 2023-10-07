/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 01:05:42 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/07 15:27:11 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_free_tab(char **tab)
{
	int        i;
    int        j;

    j = 0;
    i = 0;
    if (!tab)
        return ;
    while (tab[j])
        j++;
    if (j == i)
    {
        free(tab);
        return ;
    }
    while (i <= j)
        free(tab[i++]);
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

void    free_cmd_tab(t_main *mini)
{
    t_parsing    *tmp;

    tmp = mini->cmd_parse;
    while (tmp)
    {
        ft_free_tab(tmp->cmd_tab);
        tmp->cmd_tab = NULL;
        tmp = tmp->next;
    }
}

void    free_cmd_lst(t_parsing *lst)
{
    t_parsing    *tmp;

    tmp = lst;
    while (tmp)
    {
        lst = tmp->next;
        if (tmp)
        {
            ft_free_lexer(tmp->redirection);
            free(tmp);
        }
        tmp = lst;
    }
    free(lst);
}