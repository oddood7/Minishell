/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote_Utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:45:54 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/01 22:54:23 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    check_set(char c, int quote)
{
    if (c == quote)
        return (1);
    return (0);
}

char    *ft_trim(t_main *mini, char const *s1, int quote)
{
    char            *str;
    size_t            start;
    size_t            end;
    size_t            i;

    start = 0;
    while (s1[start] && check_set(s1[start], quote))
        start++;
    end = ft_strlen(s1);
    while (end > start && check_set(s1[end - 1], quote))
        end--;
    str = malloc(sizeof(char) * (end - start + 1));
    if (!str)
        err_mall(mini);
    i = 0;
    while (start < end)
    {
        str[i] = s1[start];
        i++;
        start++;
    }
    str[i] = '\0';
    return (str);
}

char    *cpquote(t_main *mini, char *s, int j, int quote)
{
    int        i;
    char    *ok;

    i = 0;
    ok = malloc(sizeof(char) * ft_strlen(s) - nb_quote(s, quote) + 1);
    if (!ok)
        err_mall(mini);
    while (s[i])
    {
        if (s[i] == quote)
            i++;
        else
            ok[j++] = s[i++];
        if (s[i] == '\0')
        {
            ok[j] = '\0';
            break ;
        }
    }
    return (ok);
}

char    *rm_quote_redir(t_main *mini, char *s, int quote, int j)
{
    char    *new;

    if (nb_quote(s, quote))
    {
        if (nb_quote(s, quote) == 2)
            new = ft_strim(mini, s, quote);
        else
            new = cpquote(mini, s, j, quote);
        return (new);
    }
    else
        return (NULL);
}

void    check_quote_redir(t_main *mini, t_lexer *node)
{
    t_lexer    *tmp;
    char    *s_trim;

    tmp = node;
    while (tmp)
    {
        if (tmp->str)
        {
            if (nb_quote(tmp->str, 39))
            {
                s_trim = rm_quote_redir(mini, tmp->str, 39, 0);
                free(tmp->str);
                tmp->str = s_trim;
            }
            else if (nb_quote(tmp->str, 34))
            {
                s_trim = rm_quote_redir(mini, tmp->str, 34, 0);
                free(tmp->str);
                tmp->str = s_trim;
            }
        }
        tmp = tmp->next;
    }
}
