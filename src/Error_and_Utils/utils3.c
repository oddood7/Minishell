/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:03:26 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/07 15:04:06 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    err_exp(char *s, int j)
{
    int    i;

    i = 0;
    if (j)
    {
        ft_putstr_fd("export: `", 2);
        while (s[i] && s[i] != '=')
            ft_putchar_fd(s[i++], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return (1);
    }
    return (0);
}

int    is_equals(char *s)
{
    int        i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '=')
            return (i);
        i++;
    }
    return (0);
}

int    check_identifier(char c)
{
    if (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
        || c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
        || c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
        || c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
        || c == '~'
        || c == '=' || c == '-' || c == '?' || c == '&' || c == '*')
    {
        return (1);
    }
    else
        return (0);
}