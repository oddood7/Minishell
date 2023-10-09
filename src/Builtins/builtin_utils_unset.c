/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:11:16 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void    dup_classic_env(t_main *mini, char **tab)
{
    int    i;

    i = 0;
    while (mini->env[i])
        i++;
    ft_free_tab(mini->env);
    mini->env = malloc(sizeof(char *) * i);
    if (!mini->env)
        err_mall(mini);
    i = 0;
    while (tab[i])
    {
        mini->env[i] = ft_strdup(tab[i]);
        i++;
    }
    mini->env[i] = 0;
    ft_free_tab(tab);
}

void    dup_exp(t_main *mini, char **tab)
{
    int    i;

    i = 0;
    while (mini->env_exp[i])
        i++;
    ft_free_tab(mini->env_exp);
    mini->env_exp = malloc(sizeof(char *) * i);
    if (!mini->env_exp)
        err_mall(mini);
    i = 0;
    while (tab[i])
    {
        mini->env_exp[i] = ft_strdup(tab[i]);
        i++;
    }
    mini->env_exp[i] = 0;
    ft_free_tab(tab);
}

char    **new_tab_env(t_main *mini, char **old_tab, char *s, int len)
{
    char    **tab;
    int        i;
    int        j;

    i = 0;
    j = 0;
    while (old_tab[i])
        i++;
    if (i == 1)
        return (NULL);
    tab = malloc(sizeof(char *) * i);
    if (!tab)
        err_mall(mini);
    i = 0;
    while (old_tab[i])
    {
        if (!ft_strncmp(old_tab[i], s, len) && old_tab[i][len] == '=')
            i++;
        else
            tab[j++] = ft_strdup(old_tab[i++]);
    }
    tab[j] = 0;
    return (tab);
}

char    **new_tab_exp(t_main *mini, char **old_tab, char *s, int len)
{
    char    **tab;
    int        i;
    int        j;

    i = 0;
    j = 0;
    while (old_tab[i])
        i++;
    tab = malloc(sizeof(char *) * i);
    if (!tab)
        err_mall(mini);
    i = 0;
    while (old_tab[i])
    {
        if (!ft_strncmp(old_tab[i], s, len + 11) && old_tab[i][len + 11] == '=')
            i++;
        else
            tab[j++] = ft_strdup(old_tab[i++]);
    }
    tab[j] = 0;
    return (tab);
}