/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:03:33 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*rv_static(int *rv)
{
	static int *rv_ptr;

	if (rv)
		rv_ptr = rv;
	return (rv_ptr);
}

void    built_move(t_parsing *node, size_t j)
{
    char    **tab;
    int        i;

    i = 0;
    if (ft_strlen(node->cmd_tab[0]) == j)
        return ;
    if (!node->cmd_tab[0][0])
        return ;
    while (node->cmd_tab[0][i] == ' ')
    {
        i++;
        if (!node->cmd_tab[0][i])
            return ;
    }
    tab = ft_split(node->cmd_tab[0], ' ');
    ft_free_tab(node->cmd_tab);
    node->cmd_tab = tab;
    return ;
}

int    find_built(char *str)
{
    if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "exit", 4))
        return (4);
    else if (!ft_strncmp(str, "export", 6))
        return (6);
    else if (!ft_strncmp(str, "cd", 2))
        return (2);
    else if (!ft_strncmp(str, "unset", 5))
        return (5);
    else
        return (-10);
}

void    parsing_tab_help(t_main *mini, t_parsing *node, int i, int len)
{
    char    *s;
    char    **tab;
    int        ok;
    int        sizetab;

	ok = 0;
    sizetab = sizeof(node->cmd_tab);
    while (++i <= sizetab)
    {
        if (node->cmd_tab[i][0])
        {
            ok = i;
            len = tab_len(node, sizetab, i);
            break ;
        }
    }
    s = malloc(sizeof(char) * len + 1);
    if (!s)
        err_mall(mini);
    parse_dup(node, sizetab, ok, s);
    tab = ft_split(s, ' ');
    free(s);
    ft_free_tab(node->cmd_tab);
    node->cmd_tab = tab;
}

void    check_tab(t_main *mini)
{
    t_parsing    *node;
    int            i;

    node = mini->cmd_parse;
    i = 0;
    while (node)
    {
        i = 0;
        if (!node->cmd_tab[0])
            return ;
        while (node->cmd_tab[i])
            i++;
        if (node->doubl == 2 || node->single == 2)
        {
            if (quote_tab(node, 0, 0))
                return ;
        }
        if (i == 1 && find_built(node->cmd_tab[0]))
            built_move(node, find_built(node->cmd_tab[0]));
        else if (nothing_tab(node->cmd_tab))
            parsing_tab_help(mini, node, -1, 0);
        node = node->next;
    }
}