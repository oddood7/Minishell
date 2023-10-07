/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:00:32 by lde-mais          #+#    #+#             */
/*   Updated: 2023/10/07 15:15:12 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *exp_var_name(t_main *mini, char *str)
{
    int        i;
    char    *tmp;

    i = 0;
    while (str[i] != '=')
        i++;
    tmp = malloc(sizeof(char) * i + 1);
    if (!tmp)
        err_mall(mini);
    i = 0;
    while (str[i] != '=')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

int    exp_var_quotes(char *str1, char *str2)
{
    int        i;
    int        j;

    i = 0;
    j = 0;
    while (str1[i] != '=')
    {
        str2[i] = str1[i];
        i++;
        j++;
    }
    str2[j++] = '=';
    str2[j++] = '"';
    i++;
    while (str1[i])
    {
        str2[j] = str1[i];
        i++;
        j++;
    }
    str2[j++] = '"';
    return (j);
}

int    exist_in_exp(t_main *mini, char *str)
{
    int        i;
    int        j;
    int        k;
    char    *name;

    i = 0;
    while (mini->env_exp[i])
    {
        j = 11;
        k = 0;
        name = malloc(sizeof(char) * ft_strlen(mini->env_exp[i]) - j + 1);
        if (!name)
            err_mall(mini);
        while (mini->env_exp[i][j] && mini->env_exp[i][j] != '=')
            name[k++] = mini->env_exp[i][j++];
        name[k] = '\0';
        if ((ft_strlen(name) - ft_strlen(str)) == 0)
        {
            if (!ft_strncmp(name, str, ft_strlen(str)))
                return (free(name), i);
        }
        free(name);
        i++;
    }
    return (-1);
}

int    exist_in_env(t_main *mini, char *str)
{
    int        i;
    int        size;

    i = 0;
    size = ft_strlen(str);
    while (mini->env[i])
    {
        if ((is_equals(mini->env[i]) - size) == 0)
        {
            if (!ft_strncmp(mini->env[i], str, size))
                return (i);
        }
        i++;
    }
    return (-1);
}