/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_addremove.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:17:20 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:17 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    var_to_env(t_main *mini, char *str)
{
    int        i;
    char    **new_tab;

    i = 0;
    while (mini->env[i])
        i++;
    new_tab = malloc(sizeof(char *) * (i + 2));
    if (!new_tab)
        err_mall(mini);
    i = 0;
    while (mini->env[i])
    {
        new_tab[i] = ft_strdup(mini->env[i]);
        i++;
    }
    new_tab[i++] = ft_strdup(str);
    new_tab[i] = 0;
    ft_free_tab(mini->env);
    mini->env = new_tab;
}

void    var_to_exp(t_main *mini, char *str)
{
    int        i;
    char    **new_tab;
    char    *tmp;

    i = 0;
    tmp = "declare -x ";
    while (mini->env_exp[i])
        i++;
    new_tab = malloc(sizeof(char *) * (i + 2));
    if (!new_tab)
        err_mall(mini);
    i = 0;
    while (mini->env_exp[i])
    {
        new_tab[i] = ft_strdup(mini->env_exp[i]);
        i++;
    }
    new_tab[i++] = ft_strjoin(tmp, str);
    new_tab[i] = 0;
    ft_free_tab(mini->env_exp);
    mini->env_exp = new_tab;
}

void    remove_env_var(t_main *mini, int index)
{
    char    **new_tab;
    int        i;
    int        j;

    i = 0;
    while (mini->env[i])
        i++;
    new_tab = malloc(sizeof(char *) * (i + 1));
    if (!new_tab)
        err_mall(mini);
    i = -1;
    while (++i < index)
        new_tab[i] = ft_strdup(mini->env[i]);
    j = i;
    i += 1;
    while (mini->env[i])
    {
        new_tab[j] = ft_strdup(mini->env[i]);
        i++;
        j++;
    }
    new_tab[j] = 0;
    ft_free_tab(mini->env);
    mini->env = new_tab;
}

void    remove_exp_var(t_main *mini, int index)
{
    char    **new_tab;
    int        i;
    int        j;

    i = 0;
    while (mini->env_exp[i])
        i++;
    new_tab = malloc(sizeof(char *) * (i + 1));
    if (!new_tab)
        err_mall(mini);
    i = -1;
    while (++i < index)
        new_tab[i] = ft_strdup(mini->env_exp[i]);
    j = i;
    i += 1;
    while (mini->env_exp[i])
    {
        new_tab[j] = ft_strdup(mini->env_exp[i]);
        i++;
        j++;
    }
    new_tab[j] = 0;
    ft_free_tab(mini->env_exp);
    mini->env_exp = new_tab;
}