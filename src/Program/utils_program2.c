/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_program2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:10:44 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    quote_tab(t_parsing *node, int i, int j)
{
    if (!node->cmd_tab[i][0])
        return (0);
    while (node->cmd_tab[i])
    {
        j = 0;
        if (ft_strlen(node->cmd_tab[i]))
        {
            while (node->cmd_tab[i][j])
            {
                if (node->cmd_tab[i][j] == ' ')
                {
                    if (node->cmd_tab[i][j] != '\0')
                        return (1);
                    while (node->cmd_tab[i][j] == ' ')
                        j++;
                    if (node->cmd_tab[i][j] != '\0')
                        return (1);
                }
                j++;
            }
        }
        i++;
    }
    return (0);
}

int    nothing_tab(char **tab)
{
    int    i;

    i = -1;
    while (tab[++i])
    {
        if (!tab[i][0])
            return (1);
    }
    return (0);
}

int    check_qt(char *s)
{
    int    i;

    i = 0;
    while (s[i])
    {
        if (s[i + 1] == '\0' || s[i + 1] == 32)
        {
            if (s[i] == 39)
                return (1);
        }
        i++;
    }
    return (0);
}

char    *parse_dup(t_parsing *node, int sizetab, int ok, char *str)
{
    int    j;
    int    k;

    k = 0;
    while (ok <= sizetab)
    {
        j = 0;
        while (node->cmd_tab[ok][j])
            str[k++] = node->cmd_tab[ok][j++];
        ok++;
        str[k++] = ' ';
        if (!node->cmd_tab[ok])
        {
            str[k] = '\0';
            break ;
        }
    }
    return (str);
}

int    tab_len(t_parsing *node, int sizetab, int i)
{
    int    len;

    len = 0;
    while (i <= sizetab)
    {
        len += ft_strlen(node->cmd_tab[i]) + 1;
        i++;
        if (!node->cmd_tab[i])
            break ;
    }
    return (len);
}