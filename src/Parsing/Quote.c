/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:42:07 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/17 15:10:51 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *malloc_space(t_main *mini, t_parsing *node, int i)
{
    int        size;
    char    *str;

    (void)mini;
    size = ft_strlen(node->cmd_tab[i]);
    str = ft_malloc(sizeof(char) * size + 1);
    return (str);
}

int    count_quotes(char *str, int quote)
{
    int        i;
    int        j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == quote)
            j++;
        i++;
    }
    return (j);
}

char    *check_4_strim(t_main *mini, t_parsing *node, int i, int quote)
{
    char    *new;
    int        len;

    len = ft_strlen(node->cmd_tab[i]);
    if (node->cmd_tab[i][0] == quote && count_quotes(node->cmd_tab[i], quote) == 2
        && node->cmd_tab[i][len - 1] == quote)
    {
        new = ft_trim(mini, node->cmd_tab[i], quote);
        //free(node->cmd_tab[i]);
        node->cmd_tab[i] = ft_strdup(new);
        return (new);
    }
    else
        return (NULL);
}

int    rm_quote(t_main *mini, t_parsing *node, int index, int quote)
{
    char    *new;
    int        j;
    int        i;

    j = 0;
    i = 0;
    new = check_4_strim(mini, node, i, quote);
    if (!new)
    {
        new = malloc_space(mini, node, index);
        while (node->cmd_tab[index][j])
        {
            if (node->cmd_tab[index][j] == quote)
                j++;
            else
                new[i++] = node->cmd_tab[index][j++];
        }
        new[i] = '\0';
        //free(node->cmd_tab[index]);
        node->cmd_tab[index] = ft_strdup(new);
    }
    //free(new);
    if (quote == 39)
        return (1);
    return (0);
}

int    quotes(t_main *mini, t_parsing *node, int i)
{
    int            j;

    j = 0;
    (void)mini;
    while (node->cmd_tab[i][j])
    {
        if (node->redirection)
            check_quote_redir(mini, node->redirection);
        if (node->cmd_tab[i][j] == 39)
            return (rm_quote(mini, node, i, 39));
        else if (node->cmd_tab[i][j] == 34)
            return (rm_quote(mini, node, i, 34));
        j++;
    }
    return (0);
}